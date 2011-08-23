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

int is_ef0(void)
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

const char *get_module_prefix(void)
{
	static char buf[80];

	if(pops_fw_version == FW_660) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "660");
	} else if(pops_fw_version == FW_639) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "639");
	} else if(pops_fw_version == FW_635) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "635");
	} else if(pops_fw_version == FW_620) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "620");
	} else if(pops_fw_version == FW_610) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "610");
	} else if(pops_fw_version == FW_600) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "600");
	} else if(pops_fw_version == FW_551) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "551");
	} else if(pops_fw_version == FW_550) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "550");
	} else if(pops_fw_version == FW_503) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "503");
	} else if(pops_fw_version == FW_501) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "501");
	} else if(pops_fw_version == FW_500) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "500");
	} else if(pops_fw_version == FW_401) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "401");
	} else if(pops_fw_version == FW_396) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "396");
	} else if(pops_fw_version == FW_393) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "393");
	} else if(pops_fw_version == FW_390) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "390");
	} else if(pops_fw_version == FW_380) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "380");
	} else if(pops_fw_version == FW_372) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "372");
	} else if(pops_fw_version == FW_371) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "371");
	} else if(pops_fw_version == FW_352) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "352");
	} else if(pops_fw_version == FW_351) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "351");
	} else if(pops_fw_version == FW_350) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "350");
	} else if(pops_fw_version == FW_340) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "340");
	} else if(pops_fw_version == FW_330) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "330");
	} else if(pops_fw_version == FW_311) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "311");
	} else if(pops_fw_version == FW_310) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "310");
	} else if(pops_fw_version == FW_303) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "303");
	} else if(pops_fw_version == FW_302) {
		sprintf(buf, "%s%s%s/", is_ef0() ? "ef" : "ms", MODULE_PATH, "302");
	} else {
		printk("%s: Unknown version: 0x%08X\n", __func__, pops_fw_version);
		printk_sync();
		asm("break");
	}

	return buf;
}

static SceUID _sceKernelLoadModule(const char *path, int flags, SceKernelLMOption *option)
{
	SceUID modid;
	char newpath[128];
	
	if(is_pops(path)) {
		if(pops_fw_version == FW_635 || pops_fw_version == FW_639 || pops_fw_version == FW_660) {
			sprintf(newpath, "%spops_%02dg.prx", get_module_prefix(), (int)(psp_model + 1));
			path = newpath;
		} else if(pops_fw_version == FW_620 || pops_fw_version == FW_610 || pops_fw_version == FW_600) {
			if(psp_model == PSP_1000 || psp_model == PSP_2000 || psp_model == PSP_3000) {
				sprintf(newpath, "%spops.prx", get_module_prefix());
			} else if(psp_model == PSP_4000 || psp_model == PSP_GO) {
				sprintf(newpath, "%spops_%02dg.prx", get_module_prefix(), (int)(psp_model + 1));
			} else {
				// 07/09/11G, try 04g driver
				sprintf(newpath, "%spops_%02dg.prx", get_module_prefix(), 4);
			}

			path = newpath;
		} else if(pops_fw_version <= FW_551) {
			sprintf(newpath, "%spops.prx", get_module_prefix());
			path = newpath;
		} else {
			printk("%s: PANIC unknown pops_fw_version 0x%08X\n", __func__, pops_fw_version);
			printk_sync();
			asm("break");
		}
	}

	modid = sceKernelLoadModule(path, flags, option);

	if(modid < 0) {
		printk("%s: load module -> 0x%08X\n", __func__, modid);

#ifdef DEBUG
		sceKernelDelayThread(2000000);
#endif
	}

	return modid;
}

static int load_start_module(const char *path)
{
	SceUID modid;
	SceModule2 *mod;

	modid = sceKernelLoadModule(path, 0, NULL);

	if(modid < 0) {
		printk("%s: %s load -> 0x%08X\n", __func__, path, modid);

#ifdef DEBUG
		sceKernelDelayThread(2000000);
#endif

		return modid;
	}

	mod = (SceModule2*) sceKernelFindModuleByUID(modid);

	if(mod != NULL) {
		fix_nid((SceModule*)mod);
	}

	modid = sceKernelStartModule(modid, 0, 0, 0, 0);

#ifdef DEBUG
	if(modid < 0) {
		printk("%s: %s start -> 0x%08X\n", __func__, path, modid);
		sceKernelDelayThread(2000000);
	}
#endif

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

	if(mod != NULL) {
		if(0 == strcmp(mod->modname, "sceImpose_Driver")) {
			fix_nid_impose((SceModule*)mod);
		}

		fix_nid((SceModule*)mod);

		if(pops_fw_version <= FW_401) {
			PspModuleImport *imp;

			if(0 == strcmp(mod->modname, "scePops_Manager")) {
				// patch sceImpose_driver import flags
				// because in 6.xx kernel scePops_Manager loads before sceImpose_driver
				imp = find_import_lib((SceModule*)mod, "sceImpose_driver");
				imp->attribute = 0x0009;
			}
		}

		if(0 == strcmp(mod->modname, "scePaf_Module")) {
			sctrlKernelSetNidResolver("scePaf", 0);

			if(pops_fw_version <= FW_401) {
				char path[128];

				sprintf(path, "%s%sproheaparea.prx", is_ef0() ? "ef" : "ms", MODULE_PATH);
				load_start_module(path);
			}
		}

		if(0 == strcmp(mod->modname, "PROPopcornManager")) {
			modid = sceKernelStartModule(modid, 4, &pops_fw_version, modstatus, opt);
		} else {
			modid = sceKernelStartModule(modid, argsize, argp, modstatus, opt);
		} 

		if(0 == strcmp(mod->modname, "scePops_Manager")) {
			u32 load_module_nid = -1;

			// use host nid, because fix_nid already fixed the load_module_nid into host one
			if(psp_fw_version == FW_660) {
				load_module_nid = 0x939E4270;
			} else if(psp_fw_version == FW_635 || psp_fw_version == FW_639) {
				load_module_nid = 0xFFB9B760;
			} else if(psp_fw_version == FW_620) {
				load_module_nid = 0xE3CCC6EA;
			} else {
				printk("%s: PANIC unknown fw 0x%08X\n", __func__, psp_fw_version);
				printk_sync();
				asm("break");
			}

			hook_import_bynid((SceModule*)mod, "ModuleMgrForKernel", load_module_nid, _sceKernelLoadModule, 0);
		} 
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
	SceModule2 *mod;

	for(i=0; i<NELEMS(g_list); ++i) {
		sprintf(modpath, "%s%s", get_module_prefix(), g_list[i].path);

		ret = replace_module(modid, argsize, argp, modstatus, opt, g_list[i].mod_name, modpath);

		if(ret >= 0) {
			return ret;
		}
	}

	(void)(mod);

	if(pops_fw_version <= FW_401) {
		sprintf(modpath, "%s%simpose.prx", is_ef0() ? "ef" : "ms", MODULE_PATH);
		sctrlKernelSetNidResolver("sceImpose_driver", 0);
		ret = replace_module(modid, argsize, argp, modstatus, opt, "sceImpose_Driver", modpath);

		if(ret >= 0) {
			if(pops_fw_version <= FW_303) {
				sprintf(modpath, "%smeaudio.prx", get_module_prefix());
				load_start_module(modpath);
			}
			
			return ret;
		}
	}

	return -1;
}
