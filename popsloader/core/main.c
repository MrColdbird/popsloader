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
#include "popsloader.h"
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

static int _sceIoOpen(const char *file, int flag, int mode)
{
	int ret;
	char path[128];

	if(0 == strcmp(file, "flash0:/kd/resource/impose.rsc")) {
		sprintf(path, "%s%s%s", is_ef0() ? "ef" : "ms", MODULE_PATH, "impose.rsc");
		file = path;
	}

	ret = sceIoOpen(file, flag, mode);

	return ret;
}

static int _sceKernelGetModel(void)
{
	if(pops_fw_version <= FW_401) {
		if(psp_model >= PSP_3000) {
			return PSP_2000;
		}
	} else if(pops_fw_version <= FW_551) {
		if(psp_model >= PSP_4000) {
			return PSP_3000;
		}
	}

	return psp_model;
}

static int popsloader_patch_chain(SceModule2 *mod)
{
	printk("%s: %s\n", __func__, mod->modname);

	if(pops_fw_version >= FW_500 && pops_fw_version <= FW_551) {
		if(0 == strcmp(mod->modname, "sceImpose_Driver")) {
			patch_sceImposeGetParam();
		}
	}

	if(pops_fw_version <= FW_401) {
		if(0 == strcmp(mod->modname, "sceImpose_Driver")) {
			u32 sceKernelGetModel_nid;

			sceKernelGetModel_nid = psp_fw_version == FW_620 ? 0x864EBFD7 : 0x458A70B5;
			hook_import_bynid((SceModule*)mod, "IoFileMgrForKernel", 0x109F50BC, _sceIoOpen, 0);
			hook_import_bynid((SceModule*)mod, "SysMemForKernel", sceKernelGetModel_nid, _sceKernelGetModel, 0);
		}
	}

	if(g_previous)
		return g_previous(mod);
	
	return 0;
}

// quick fix for kernel module
void* sceGeEdramGetAddr(void)
{
	return (void*)0x44000000;
}

int test_thread(SceSize args, void *argp)
{
	int ret;
	SceModule* mod;

	ret = sceKernelLoadModule("ms0:/seplugins/popsloader/modules/635/popsman.prx", 0, NULL);
	mod = sceKernelFindModuleByUID(ret);
	fix_nid(mod);
	ret = sceKernelStartModule(ret, 0, 0, 0, 0);

	return 0;
}

// for those FW required idmanager.prx
int sceIdMgr_driver_F464F91C(void)
{
	return 0;
}

int module_start(SceSize args, void* argp)
{
	int thid;

	psp_fw_version = sceKernelDevkitVersion();
	psp_model = sceKernelGetModel();
	printk_init("ms0:/core.txt");
	mount_memory_stick();

	if(-1 == load_config() || g_conf.pops_fw_version == 0) {
		return 1;
	}

	pops_fw_version = g_conf.pops_fw_version;
	setup_nid_resolver();
	setup_nid_resolver_impose();
	sctrlSetCustomStartModule(&custom_start_module);
	g_previous = sctrlHENSetStartModuleHandler(&popsloader_patch_chain);

	(void)thid;

#if 0
	thid = sceKernelCreateThread("test", test_thread, 0x1A, 0xF00, 0, NULL);

	if(thid>=0) {
		sceKernelStartThread(thid, args, argp);
	}
#endif
	
	return 0;
}
