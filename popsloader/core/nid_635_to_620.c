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

static nid_entry SysMemForKernel_nid[] = {
	{ 0x25A760F0, 0x02AEA33F, },
	{ 0x2CFE3B22, 0x74F3DC82, },
	{ 0x3DE3C6DF, 0xF5780DAA, },
	{ 0x458A70B5, 0x864EBFD7, },
	{ 0x52B54B93, 0xFEB5C72B, },
	{ 0xF0E0AB7A, 0xB9796F69, },
	{ 0xF2FEAFD5, 0xA4AC3934, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xFCD765C9, 0x29413885, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0xE6BF3960, 0xDF8FFFAB, },
	{ 0xFFB9B760, 0xE3CCC6EA, },
};

static nid_entry sceRtc_driver_nid[] = {
	{ 0x99037763, 0x7ED29E40, },
	{ 0xFF530D9F, 0x2F20DAF0, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x027F21C6, 0x25011AAB, },
	{ 0x3BD9E51B, 0x5314204F, },
	{ 0x3FE74F52, 0x8F1AC24D, },
	{ 0x44F17A7A, 0x55864BD7, },
	{ 0x4C4DF719, 0xC94AC8E2, },
	{ 0xEBC850AC, 0x4D849B71, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x3A98CABB, 0x9EBB3C43, },
	{ 0x789597AB, 0xE7849809, },
	{ 0x86FFE348, 0x119647A7, },
	{ 0x8E9E76AE, 0xB733A263, },
	{ 0x9984A972, 0x94914740, },
	{ 0x9E80B4E2, 0x47966D28, },
	{ 0xB70793D7, 0x97EA6913, },
	{ 0xD1999F94, 0x5D3DD0B3, },
	{ 0xD74D9041, 0x2B3BE2C8, },
	{ 0xE2606FCB, 0x2D858336, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x741110C5, 0xB757C11D, },
	{ 0xC4931159, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xA02BB1D3, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0xFEEC36F7, 0x23E9F5FA, },
	{ 0xD8A53104, 0x7E2381D2, },
	{ 0x2444EC4D, 0xD4D665C9, },
	{ 0x670F15ED, 0xF489E74B, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x3E4B1B28, 0x0F82D90A, },
	{ 0x3DABE438, 0xAAC50D73, },
	{ 0x8930B3A9, 0xF4B7B531, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0xADE4B1F4, 0x62CDFB12, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0xAA085C2A, 0xA1401BA2, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0xB2EF6B19, 0x794EE731, },
};

static nid_entry sceCtrl_driver_nid[] = {
	{ 0xDEFAD580, 0x7A6436DE, },
};

static nid_entry scePadSvc_driver_nid[] = {
	{ 0x2F9A534A, 0x3B0567D6, },
	{ 0x773BA62B, 0x79B60777, },
	{ 0x830FC570, 0x1971BAE0, },
};

static nid_entry InitForKernel_nid[] = {
	{ 0xEE67E450, 0x977A0F90, },
};

resolver_config nid_fix_635_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceRtc_driver),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceDisplay_driver),
	NID_ENTRY(sceHprm_driver),
	NID_ENTRY(sceDve_driver),
	NID_ENTRY(sceCodec_driver),
	NID_ENTRY(sceCtrl_driver),
	NID_ENTRY(scePadSvc_driver),
	NID_ENTRY(InitForKernel),
};

u32 nid_fix_635_to_620_size = NELEMS(nid_fix_635_to_620);
