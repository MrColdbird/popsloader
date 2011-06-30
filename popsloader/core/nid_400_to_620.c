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
	{ 0x12720EDA, 0xB9796F69, },
	{ 0x3EEE43C5, 0xA4AC3934, },
	{ 0x5136926D, 0xFEB5C72B, },
	{ 0x523E300A, 0xF5780DAA, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x24C5ABC2, 0xE3CCC6EA, },
	{ 0x63A3CAFB, 0xDF8FFFAB, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x63D88393, 0x29413885, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x15574362, 0x9EBB3C43, },
	{ 0x21797DCF, 0x94914740, },
	{ 0x23D205CA, 0x774775CA, },
	{ 0x643169E5, 0xE7849809, },
	{ 0x67583EF1, 0xB733A263, },
	{ 0x88E26FBC, 0x34EED467, },
	{ 0x8E6586AD, 0x2D858336, },
	{ 0xA36C4E9E, 0x97EA6913, },
	{ 0xB60FBA15, 0x2B3BE2C8, },
	{ 0xC4B60AB3, 0x47966D28, },
	{ 0xD80E8AAF, 0x119647A7, },
	{ 0xD83733C9, 0x4643F826, },
	{ 0xE08034E0, 0x5D3DD0B3, },
	{ 0xE65B0490, 0x314A489C, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x581D72B2, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x17FA615B, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x1DDA69CE, 0xD4D665C9, },
	{ 0xA402A161, 0x23E9F5FA, },
	{ 0xC545B81E, 0x862248FD, },
	{ 0xDC09D302, 0x7E2381D2, },
	{ 0xF5423CAA, 0xF489E74B, },
};

resolver_config nid_fix_400_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
};

u32 nid_fix_400_to_620_size = NELEMS(nid_fix_400_to_620);
