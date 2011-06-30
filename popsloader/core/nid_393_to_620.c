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
	{ 0x539F8A51, 0xA4AC3934, },
	{ 0x9110439F, 0xB9796F69, },
	{ 0xBC3AFFF2, 0xFEB5C72B, },
	{ 0xE151223E, 0xF5780DAA, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x1D313DE9, 0xDF8FFFAB, },
	{ 0xAE802E8F, 0xE3CCC6EA, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xAE5AC5D3, 0x29413885, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x0A0F9644, 0xEF64EFDD, },
	{ 0x0F8D83B8, 0x9EBB3C43, },
	{ 0x26A0937D, 0x97EA6913, },
	{ 0x31D046A0, 0x774775CA, },
	{ 0x33E54489, 0xF6922705, },
	{ 0x418CCE8D, 0x47966D28, },
	{ 0x49F7F222, 0x2D858336, },
	{ 0x7AC62361, 0x5D3DD0B3, },
	{ 0xA837DCEB, 0x94914740, },
	{ 0xB87B15D4, 0x119647A7, },
	{ 0xD040B7AB, 0x314A489C, },
	{ 0xD3CD4CC8, 0xE7849809, },
	{ 0xEE11D026, 0x34EED467, },
	{ 0xF8623D08, 0xB733A263, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0xAE31405A, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x87CEDE80, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x0C15B44A, 0xD4D665C9, },
	{ 0x4659CC7C, 0x7E2381D2, },
	{ 0x7008C80C, 0x23E9F5FA, },
	{ 0x8B2CE4CE, 0xF489E74B, },
	{ 0xB267CB88, 0x862248FD, },
};

// for 4.01 impose.prx 
static nid_entry sceImpose_driver_nid[] = {
	{ 0x21D3EA22, 0x6F502C0A, },
	{ 0xD4FDA428, 0xCD1291FD, },
	{ 0xFC9B1843, 0x869EB4A8, },
};

resolver_config nid_fix_393_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
};

u32 nid_fix_393_to_620_size = NELEMS(nid_fix_393_to_620);
