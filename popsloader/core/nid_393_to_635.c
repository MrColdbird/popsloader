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
	{ 0x539F8A51, 0xF2FEAFD5, },
	{ 0x9110439F, 0xF0E0AB7A, },
	{ 0xBC3AFFF2, 0x52B54B93, },
	{ 0xE151223E, 0x208F4820, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x1D313DE9, 0xE6BF3960, },
	{ 0xAE802E8F, 0xFFB9B760, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xAE5AC5D3, 0xFCD765C9, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x0A0F9644, 0xD74D9041, },
	{ 0x0F8D83B8, 0x3A98CABB, },
	{ 0x26A0937D, 0xB70793D7, },
	{ 0x31D046A0, 0x64FA9D42, },
	{ 0x33E54489, 0x45596E3F, },
	{ 0x418CCE8D, 0x9E80B4E2, },
	{ 0x49F7F222, 0xE2606FCB, },
	{ 0x7AC62361, 0xD1999F94, },
	{ 0xA837DCEB, 0x9984A972, },
	{ 0xB87B15D4, 0x86FFE348, },
	{ 0xD040B7AB, 0x0CFD5A8A, },
	{ 0xD3CD4CC8, 0x789597AB, },
	{ 0xEE11D026, 0x035BD7AA, },
	{ 0xF8623D08, 0x8E9E76AE, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0xAE31405A, 0xC4931159, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x87CEDE80, 0xA02BB1D3, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x0C15B44A, 0x2444EC4D, },
	{ 0x4659CC7C, 0xD8A53104, },
	{ 0x7008C80C, 0xFEEC36F7, },
	{ 0x8B2CE4CE, 0x670F15ED, },
	{ 0xB267CB88, 0xEF1B48C6, },
};

// for 4.01 impose.prx 
static nid_entry sceImpose_driver_nid[] = {
	{ 0x21D3EA22, 0x6F502C0A, },
	{ 0xD4FDA428, 0xCD1291FD, },
	{ 0xFC9B1843, 0x869EB4A8, },
};

resolver_config nid_fix_393_to_635[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
};

u32 nid_fix_393_to_635_size = NELEMS(nid_fix_393_to_635);
