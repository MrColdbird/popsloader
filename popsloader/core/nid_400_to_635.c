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
	{ 0x12720EDA, 0xF0E0AB7A, },
	{ 0x3EEE43C5, 0xF2FEAFD5, },
	{ 0x5136926D, 0x52B54B93, },
	{ 0x523E300A, 0x208F4820 , },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x24C5ABC2, 0xFFB9B760, },
	{ 0x63A3CAFB, 0xE6BF3960, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x63D88393, 0xFCD765C9, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x15574362, 0x3A98CABB, },
	{ 0x21797DCF, 0x9984A972, },
	{ 0x23D205CA, 0x64FA9D42, },
	{ 0x643169E5, 0x789597AB, },
	{ 0x67583EF1, 0x8E9E76AE, },
	{ 0x88E26FBC, 0x035BD7AA, },
	{ 0x8E6586AD, 0xE2606FCB, },
	{ 0xA36C4E9E, 0xB70793D7, },
	{ 0xB60FBA15, 0xD74D9041, },
	{ 0xC4B60AB3, 0x9E80B4E2, },
	{ 0xD80E8AAF, 0x86FFE348, },
	{ 0xD83733C9, 0x45596E3F, },
	{ 0xE08034E0, 0xD1999F94, },
	{ 0xE65B0490, 0x0CFD5A8A, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x581D72B2, 0xC4931159, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x17FA615B, 0xA02BB1D3, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x1DDA69CE, 0x2444EC4D, },
	{ 0xA402A161, 0xFEEC36F7, },
	{ 0xC545B81E, 0xEF1B48C6, },
	{ 0xDC09D302, 0xD8A53104, },
	{ 0xF5423CAA, 0x670F15ED, },
};

resolver_config nid_fix_400_to_635[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
};

u32 nid_fix_400_to_635_size = NELEMS(nid_fix_400_to_635);
