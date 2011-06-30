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
	{ 0x9D9A5BA1, 0x52B54B93, },
	{ 0xCDA3A2F7, 0xF2FEAFD5, },
	{ 0xCF4DE78C, 0x208F4820, },
	{ 0xFC114573, 0xF0E0AB7A, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x50F0C1EC, 0xE6BF3960, },
	{ 0x977DE386, 0xFFB9B760, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x6D302D3D, 0xFCD765C9, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x07881A0B, 0x64FA9D42, },
	{ 0x0C7E4512, 0x3A98CABB, },
	{ 0x1CD747DC, 0x035BD7AA, },
	{ 0x27C0A714, 0x8E9E76AE, },
	{ 0x3199CF1C, 0xD74D9041, },
	{ 0x38CD3AB5, 0xD1999F94, },
	{ 0x545CE0A8, 0x9984A972, },
	{ 0x595C27FB, 0x789597AB, },
	{ 0x6C305CB3, 0x9E80B4E2, },
	{ 0x76220E94, 0xE2606FCB, },
	{ 0xA57CBE53, 0x45596E3F, },
	{ 0xA9997109, 0xB70793D7, },
	{ 0xB2C9B019, 0x0CFD5A8A, },
	{ 0xE5B3D348, 0x86FFE348, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x4E5C5F26, 0xC4931159, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xD4F6990D, 0xA02BB1D3, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x264E8BED, 0xFEEC36F7, },
	{ 0x2FA58122, 0xEF1B48C6, },
	{ 0x58C59880, 0x2444EC4D, },
	{ 0xBA035FC8, 0x670F15ED, },
};

// for 4.01 impose.prx 
static nid_entry sceImpose_driver_nid[] = {
	{ 0x531C9778, 0x6F502C0A, },
	{ 0x8C943191, 0x869EB4A8, },
	{ 0xB415FC59, 0xCD1291FD, },
};

resolver_config nid_fix_373_to_635[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceImpose_driver),
};

u32 nid_fix_373_to_635_size = NELEMS(nid_fix_373_to_635);
