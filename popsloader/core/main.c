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
#include <systemctrl.h>
#include <systemctrl_se.h>
#include <pspsysmem_kernel.h>
#include <pspiofilemgr_kernel.h>
#include <psprtc.h>
#include "utils.h"
#include "libs.h"
#include "strsafe.h"
#include "systemctrl.h"
#include "main.h"

PSP_MODULE_INFO("popscore", 0x1007, 1, 0);

u32 psp_fw_version;
u32 psp_model;
u32 pops_fw_version;

static STMOD_HANDLER g_previous = NULL;

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

static inline int is_pops(const char *path)
{
	const char *q;

	if(path == NULL)
		return 0;

	q = strrchr(path, '/');

	if(q != NULL) {
		q++;
	} else {
		q = path;
	}

	if(0 == strcmp(q, "pops.prx")) {
		return 1;
	}

	if(0 == strncmp(q, "pops_", sizeof("pops_") - 1)) {
		return 1;
	}

	return 0;
}

static SceUID _sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option)
{
	SceUID modid;
	char newpath[128];
	
	if(is_pops(path)) {
		if(pops_fw_version == FW_635) {
			sprintf(newpath, MODULE_PATH "635/" "pops_%02dg.prx", (int)(psp_model + 1));
			path = newpath;
		} else {
			asm("break");
		}
	}

	modid = sceKernelLoadModule(path, flags, option);

	return modid;
}

static int check_module(int modid, SceSize argsize, void *argp, int *modstatus, SceKernelSMOption *opt, char *modname, char *redir_path)
{
	SceModule2 *mod;
	int ret;

	mod = (SceModule2*) sceKernelFindModuleByUID(modid);

	if(mod == NULL) {
		return -1;
	}

	if(0 != strcmp(mod->modname, modname)) {
		return -2;
	}

	ret = sceKernelUnloadModule(modid);

	if(ret < 0) {
		printk("%s: unload %s -> 0x%08X\n", __func__, modname, ret);
		sceKernelDelayThread(1000000);
		return ret;
	}

	if(redir_path == NULL) {
		return 0;
	}

	modid = sceKernelLoadModule(redir_path, 0, NULL);

	if(modid < 0) {
		printk("%s: load module %s -> 0x%08X\n", __func__, redir_path, modid);
		sceKernelDelayThread(1000000);
		return modid;
	}

	mod = (SceModule2*) sceKernelFindModuleByUID(modid);
	resolve_nid((SceModule*)mod);
	modid = sceKernelStartModule(modid, argsize, argp, modstatus, opt);

	if(0 == strcmp(mod->modname, "scePops_Manager")) {
		u32 load_module_nid;

		if(pops_fw_version == FW_635) {
			load_module_nid = 0xFFB9B760;
		}

		hook_import_bynid((SceModule*)mod, "ModuleMgrForKernel", load_module_nid, _sceKernelLoadModule, 0);
	}
	
	printk("%s: start module %s -> 0x%08X\n", __func__, redir_path, modid);

	return modid;
}

int custom_start_module(int modid, SceSize argsize, void *argp, int *modstatus, SceKernelSMOption *opt)
{
	int ret;

	ret = check_module(modid, argsize, argp, modstatus, opt, "scePops_Manager", MODULE_PATH "635/" "popsman.prx");

	if(ret >= 0) {
		return ret;
	}

	ret = check_module(modid, argsize, argp, modstatus, opt, "PROPopcornManager", MODULE_PATH "635/" "popcorn.prx");

	if(ret >= 0) {
		return ret;
	}

	return -1;
}

static int popsloader_patch_chain(SceModule2 *mod)
{
	printk("%s: %s\n", __func__, mod->modname);

	if(g_previous)
		return g_previous(mod);
	
	return 0;
}

// quick fix for kernel module
void* sceGeEdramGetAddr(void)
{
	return (void*)0x44000000;
}

int module_start(SceSize args, void* argp)
{
	pops_fw_version = FW_635;
	psp_fw_version = sceKernelDevkitVersion();
	psp_model = sceKernelGetModel();
	pspDebugScreenInit();
	mount_memory_stick();
	sctrlSetCustomStartModule(&custom_start_module);
	g_previous = sctrlHENSetStartModuleHandler(&popsloader_patch_chain);

	return 0;
}
