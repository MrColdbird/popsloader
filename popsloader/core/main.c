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

struct ModuleList {
	char *path;
	char *mod_name;
};

PSP_MODULE_INFO("popscore", 0x1007, 1, 0);

u32 psp_fw_version;
u32 psp_model;
u32 pops_fw_version;

static STMOD_HANDLER g_previous = NULL;

static inline int is_ef0(void)
{
	return psp_model == PSP_GO && sctrlKernelBootFrom() == 0x50 ? 1 : 0;
}

void mount_memory_stick(void)
{
	int dfd;
	char *devname = "ms0:/";

	if(is_ef0()) {
		devname = "ef0:/";
	}

	do {
		dfd = sceIoDopen(devname);

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

static inline const char *get_module_prefix(void)
{
	static char buf[80];

	if(pops_fw_version == FW_639) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "639");
	} else if(pops_fw_version == FW_635) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "635");
	} else if(pops_fw_version == FW_620) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "620");
	} else if(pops_fw_version == FW_610) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "610");
	} else if(pops_fw_version == FW_600) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "600");
	} else if(pops_fw_version == FW_500) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "500");
	} else {
		printk("%s: Unknown version: 0x%08X\n", __func__, pops_fw_version);
		asm("break");
	}

	return buf;
}

static SceUID _sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option)
{
	SceUID modid;
	char newpath[128];
	
	if(is_pops(path)) {
		if(pops_fw_version == FW_635 || pops_fw_version == FW_639) {
			sprintf(newpath, "%spops_%02dg.prx", get_module_prefix(), (int)(psp_model + 1));
			path = newpath;
		} else if(pops_fw_version == FW_620 || pops_fw_version == FW_610 || pops_fw_version == FW_600) {
			if(psp_model == PSP_1000 || psp_model == PSP_2000 || psp_model == PSP_3000) {
				sprintf(newpath, "%spops.prx", get_module_prefix());
			} else if(psp_model == PSP_4000 || psp_model == PSP_GO) {
				sprintf(newpath, "%spops_%02dg.prx", get_module_prefix(), (int)(psp_model + 1));
			} else {
				// 07g and 09g, try 04g driver
				sprintf(newpath, "%spops_%02dg.prx", get_module_prefix(), 4);
			}

			path = newpath;
		} else if(pops_fw_version == FW_500) {
			sprintf(newpath, "%spops.prx", get_module_prefix());
			path = newpath;
		} else {
			asm("break");
		}
	}

	modid = sceKernelLoadModule(path, flags, option);

	if(modid < 0) {
		printk("%s: load module -> 0x%08X\n", __func__, modid);
	}

	return modid;
}

static int replace_module(int modid, SceSize argsize, void *argp, int *modstatus, SceKernelSMOption *opt, char *modname, char *redir_path)
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

#ifdef DEBUG
		sceKernelDelayThread(2000000);
#endif

		return ret;
	}

	if(redir_path == NULL) {
		return 0;
	}

	modid = sceKernelLoadModule(redir_path, 0, NULL);

	if(modid < 0) {
		printk("%s: load module %s -> 0x%08X\n", __func__, redir_path, modid);

#ifdef DEBUG
		sceKernelDelayThread(2000000);
#endif

		return modid;
	}

	mod = (SceModule2*) sceKernelFindModuleByUID(modid);
	fix_nid((SceModule*)mod);

	if(0 == strcmp(mod->modname, "PROPopcornManager")) {
		modid = sceKernelStartModule(modid, 4, &pops_fw_version, modstatus, opt);
	} else {
		modid = sceKernelStartModule(modid, argsize, argp, modstatus, opt);
	}

	if(0 == strcmp(mod->modname, "scePops_Manager")) {
		u32 load_module_nid = -1;

		// use host nid, because fix_nid already fixed the load_module_nid into host one
		if(psp_fw_version == FW_635 || psp_fw_version == FW_639) {
			load_module_nid = 0xFFB9B760;
		} else if(psp_fw_version == FW_620) {
			load_module_nid = 0xE3CCC6EA;
		} else {
			printk("%s: unknown fw 0x%08X\n", __func__, psp_fw_version);
			asm("break");
		}

		hook_import_bynid((SceModule*)mod, "ModuleMgrForKernel", load_module_nid, _sceKernelLoadModule, 0);
	}
	
	printk("%s: start module %s -> 0x%08X\n", __func__, redir_path, modid);

#ifdef DEBUG
	if(modid < 0) {
		sceKernelDelayThread(2000000);
	}
#endif

	return modid;
}

static struct ModuleList g_list[] = {
	{ "popsman.prx",		"scePops_Manager" },
	{ "popcorn.prx",		"PROPopcornManager" },
	{ "libpspvmc.prx",		"pspvmc_Library" },
	{ "pafmini.prx",		"scePaf_Module" },
	{ "common_util.prx",	"sceVshCommonUtil_Module" },
};

int custom_start_module(int modid, SceSize argsize, void *argp, int *modstatus, SceKernelSMOption *opt)
{
	int ret, i;
	char modpath[128];

	for(i=0; i<NELEMS(g_list); ++i) {
		sprintf(modpath, "%s%s", get_module_prefix(), g_list[i].path);

		ret = replace_module(modid, argsize, argp, modstatus, opt, g_list[i].mod_name, modpath);

		if(ret >= 0) {
			return ret;
		}
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

int module_start(SceSize args, void* argp)
{
	int thid;

	pops_fw_version = FW_639;
	psp_fw_version = sceKernelDevkitVersion();
	psp_model = sceKernelGetModel();
	printk_init();
	mount_memory_stick();

	if(-1 == load_config() || g_conf.pops_fw_version == psp_fw_version) {
		return 1;
	}

	pops_fw_version = g_conf.pops_fw_version;
	setup_nid_resolver();
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
