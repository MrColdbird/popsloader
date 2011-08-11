/*
 * This file is part of PRO CFW.

 * PRO CFW is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * PRO CFW is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PRO CFW. If not, see <http://www.gnu.org/licenses/ .
 */

#include <pspkernel.h>
#include <pspreg.h>
#include <stdio.h>
#include <string.h>
#include <pspsysmem_kernel.h>
#include <pspthreadman_kernel.h>
#include <pspctrl.h>
#include <pspiofilemgr_kernel.h>
#include <psprtc.h>
#include "popsloader.h"
#include "utils.h"
#include "libs.h"
#include "strsafe.h"
#include "systemctrl.h"
#include "systemctrl_se.h"
#include "main.h"

PSP_MODULE_INFO("popsloader", 0x1007, 1, 0);

u32 psp_fw_version;
u32 psp_model;
void *module_buffer = NULL;
u32 module_size = 0;
STMOD_HANDLER g_previous = NULL;

int is_ef0(void)
{
	return psp_model == PSP_GO && sctrlKernelBootFrom() == 0x50 ? 1 : 0;
}

void mount_memory_stick(void)
{
	int dfd;

	do {
		dfd = sceIoDopen("ms0:/");

		if(dfd >= 0)
			break;

		sceKernelDelayThread(100000);
	} while (1);

	printk("%s: OK...\n", __func__);

	sceIoDclose(dfd);
}

u8 *alloc_mem(int bufsiz)
{
	int memid;
	void *module_buffer;

	memid = sceKernelAllocPartitionMemory(1, "module_buffer", 1, bufsiz + 64, 0);

	if (memid >= 0) {
		module_buffer = sceKernelGetBlockHeadAddr(memid);
		module_buffer = (u8*)(void*)(((u32)module_buffer & (~(64-1))) + 64);

		return module_buffer;
	}

	return NULL;
}

static void reboot_vsh_with_error(u32 error)
{
	struct SceKernelLoadExecVSHParam param;	
	u32 vshmain_args[0x20/4];

	memset(&param, 0, sizeof(param));
	memset(vshmain_args, 0, sizeof(vshmain_args));

	vshmain_args[0/4] = 0x0400;
	vshmain_args[4/4] = 0x20;
	vshmain_args[0x14/4] = error;

	param.size = sizeof(param);
	param.args = 0x400;
	param.argp = vshmain_args;
	param.vshmain_args_size = 0x400;
	param.vshmain_args = vshmain_args;
	param.configfile = "/kd/pspbtcnf.txt";

	sctrlKernelExitVSH(&param);
}

int load_popsloader(void)
{
	int fd;
	char path[256];

	sprintf(path, "%s%s", is_ef0() ? "ef" : "ms", BASE_PATH "popscore.prx");
	fd = sceIoOpen(path, PSP_O_RDONLY, 0);

	if (fd < 0) {
		printk("%s: sceIoOpen@0x%08X\n", __func__, fd);

		return  fd;
	}

	module_size = sceIoLseek(fd, 0, PSP_SEEK_END);
	module_buffer = alloc_mem(module_size);

	if (module_buffer == NULL) {
		printk("alloc_mem(%d) failed\n", module_size);
		sceIoClose(fd);

		return -1;
	}

	sceIoLseek(fd, 0, PSP_SEEK_SET);
	sceIoRead(fd, module_buffer, module_size);
	sctrlHENLoadModuleOnReboot("/kd/utility.prx", module_buffer, module_size, BOOTLOAD_GAME | BOOTLOAD_POPS | BOOTLOAD_UMDEMU);
	sceIoClose(fd);

	return 0;
}

int launch_pops(char *path)
{
	struct SceKernelLoadExecVSHParam param;
	int apitype, ret;
	const char *mode;

	apitype = is_ef0() ? 0x155: 0x144;
	mode = "pops";

	printk("%s: apitype 0x%X\n", __func__, apitype);

	memset(&param, 0, sizeof(param));
	param.size = sizeof(param);
	param.args = strlen(path) + 1;
	param.argp = (char *) path;
	param.key = mode;

	ret = sctrlKernelLoadExecVSHWithApitype(apitype, path, &param);

	return ret;
}

static char g_initfile[256];

static void loadexec_pops(void)
{
	int ret, status;

	ret = load_popsloader();

	if(ret < 0) {
		reboot_vsh_with_error(ret);
	}

	printk("init_file = %s\n", g_initfile);
	ret = launch_pops(g_initfile);
	printk("launch_pops -> 0x%08X\n", ret);

	if(ret < 0) {
		reboot_vsh_with_error(ret);
	}

	ret = sceKernelStopUnloadSelfModule(0, NULL, &status, NULL);
}

int launch_thread(SceSize args, void *argp)
{
	printk("%s: started\n", __func__);
	loadexec_pops();

	return 0;
}

int ui_thread(SceSize args, void *argp)
{
	printk("%s: started\n", __func__);
	get_pops_fw_version(&g_conf.pops_fw_version);
	save_config();
	loadexec_pops();

	return 0;
}

static SceUID create_thread(int is_ui_thread)
{
	SceUID thid;
	char *thread_name;
	void *fp;

	if(is_ui_thread) {
		thread_name = "ui_thread";
		fp = &ui_thread;
	} else {
		thread_name = "launch_thread";
		fp = &launch_thread;
	}

	thid = sceKernelCreateThread(thread_name, fp, 0x1A, 0xF00, 0, NULL);

	if(thid >= 0) {
		sceKernelStartThread(thid, 0, NULL);
	}

	return thid;
}

int popsloader_patch_chain(SceModule2 *mod)
{
	printk("%s: %s\n", __func__, mod->modname);

	if(0 == strcmp(mod->modname, "pops")) {
		MAKE_DUMMY_FUNCTION_RETURN_1(mod->entry_addr);
		sync_cache();
		create_thread(1);
	}

	if(g_previous)
		return g_previous(mod);
	
	return 0;
}

int module_start(SceSize args, void* argp)
{
	SceCtrlData ctrl_data;
	char *init_file;

	init_file = sceKernelInitFileName();
	strcpy(g_initfile, init_file);

	// popscore loaded, no need to reboot
	if(sceKernelFindModuleByName("popscore") != NULL) {
		return 1;
	}
	
	psp_fw_version = sceKernelDevkitVersion();
	psp_model = sceKernelGetModel();
	printk_init();
	mount_memory_stick();
	load_config();

	sceCtrlReadBufferPositive(&ctrl_data, 1);

	if(ctrl_data.Buttons & PSP_CTRL_RTRIGGER) {
		g_previous = sctrlHENSetStartModuleHandler(&popsloader_patch_chain);
	} else if(g_conf.pops_fw_version != 0) {
		create_thread(0);
	}
	
	return 0;
}

// quick fix for kernel module
void* sceGeEdramGetAddr(void)
{
	return (void*)0x44000000;
}
