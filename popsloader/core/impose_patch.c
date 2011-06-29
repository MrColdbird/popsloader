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

static u32 g_sceImposeGetParamOld_NID[] = {
	0x4B02F047,
	0x531C9778,
	0x6F502C0A,
	0x4C4DF719,
	0xC94AC8E2,
};

static int (*sceImposeGetParamNew)(int param) = NULL;

static int _sceImposeGetParamOld(int param)
{
	int new_param, ret;

	/* 0x00000001 -> 0x00000001 */
	/* 0x00000002 -> 0x00000002 */
	/* 0x00000004 -> 0x00000004 */
	/* 0x00000008 -> 0x00000008 */
	/* 0x00000010 -> 0x00000010 */
	/* 0x00000020 -> 0x00000020 */
	/* 0x00000040 -> 0x00000040 */
	/* 0x00000080 -> 0x00000080 */

	switch(param) {
		case 0x00000200:
			new_param = 0x80000002;
			break;
		case 0x00000400:
			new_param = 0x80000003;
			break;
		case 0x00000800:
			new_param = 0x00000100;
			break;
		case 0x00001000:
			new_param = 0x00000200;
			break;
		case 0x00004000:
			new_param = 0x80000005;
			break;
		case 0x00008000:
			new_param = 0x80000006;
			break;
		case 0x00010000:
			new_param = 0x80000009;
			break;
		case 0x00020000:
			new_param = 0x00000400;
			break;
		case 0x00100000:
			new_param = 0x8000000A;
			break;
		case 0x00200000:
			new_param = 0x8000000B;
			break;
		case 0x00400000:
			new_param = 0x20000000;
			break;
		default:
			new_param = param;
	}

	ret = (*sceImposeGetParamNew)(new_param);

	if(ret < 0) {
		printk("%s: 0x%08X/0x%08X -> 0x%08X\n", __func__, param, new_param, ret);
	}

	return ret;
}

void patch_sceImposeGetParam(void)
{
	SceModule2 *mod;
	u32 sceImposeGetParam_NID = -1;
	int i;

	if(psp_fw_version == FW_620) {
		sceImposeGetParam_NID = 0xC94AC8E2;
	} else if(psp_fw_version == FW_635 || psp_fw_version == FW_639) {
		sceImposeGetParam_NID = 0x4C4DF719;
	} else {
		asm("break");
	}

	sceImposeGetParamNew = (void*)sctrlHENFindFunction("sceImpose_Driver", "sceImpose_driver", sceImposeGetParam_NID);
	mod = (SceModule2*)sceKernelFindModuleByName("scePops_Manager");

	for(i=0; i<NELEMS(g_sceImposeGetParamOld_NID); ++i) {
		hook_import_bynid((SceModule*)mod, "sceImpose_driver", g_sceImposeGetParamOld_NID[i], _sceImposeGetParamOld, 0);
	}
}
