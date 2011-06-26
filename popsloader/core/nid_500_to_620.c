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
	{ 0x2CFF6F90, 0xB9796F69, },
	{ 0x5339A163, 0xA4AC3934, },
	{ 0x950BCB31, 0xFEB5C72B, },
	{ 0xD7E24299, 0xF5780DAA, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0xBB8C8FDF, 0xDF8FFFAB, },
	{ 0xC5A281C5, 0xE3CCC6EA, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x9C9BB2D8, 0x29413885, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x0BBCA0BF, 0x55864BD7, },
	{ 0xA516434B, 0x4D849B71, },
	{ 0xDA315C59, 0x25011AAB, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x08E0EE7E, 0xEF64EFDD, },
	{ 0x0E6301D0, 0x314A489C, },
	{ 0x20C9E2C4, 0x97EA6913, },
	{ 0x410C74F7, 0x5D3DD0B3, },
	{ 0x461B8077, 0x4643F826, },
	{ 0x48869494, 0x47966D28, },
	{ 0x5F190A4E, 0x2D858336, },
	{ 0x663D5471, 0x119647A7, },
	{ 0x7A154A45, 0x34EED467, },
	{ 0x823FFD7A, 0xB733A263, },
	{ 0x923509A1, 0x9EBB3C43, },
	{ 0xC7FC7669, 0xE7849809, },
	{ 0xE46A0890, 0x94914740, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x48728250, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xD1A8E10E, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x0C9C3686, 0x7E2381D2, },
	{ 0x1F226BA9, 0xD4D665C9, },
	{ 0x6663F1BD, 0xF489E74B, },
	{ 0x6849A0B0, 0x23E9F5FA, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x10B1710B, 0xF4B7B531, }, // not very exactly
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0xF5DBC7AA, 0x62CDFB12, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x0CC96C20, 0xA1401BA2, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0xA48DE786, 0x794EE731, },
};

resolver_config nid_fix_500_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceDisplay_driver),
	NID_ENTRY(sceHprm_driver),
	NID_ENTRY(sceDve_driver),
	NID_ENTRY(sceCodec_driver),
};

u32 nid_fix_500_to_620_size = NELEMS(nid_fix_500_to_620);
