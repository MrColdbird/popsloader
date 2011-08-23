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
	{ 0x9D9A5BA1, 0xF12A62F7, },
	{ 0xCDA3A2F7, 0xFDC97D28, },
	{ 0xCF4DE78C, 0x9F205D3E, },
	{ 0xFC114573, 0xB4F00CB5, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x50F0C1EC, 0x3FF74DF1, },
	{ 0x977DE386, 0x939E4270, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x6D302D3D, 0xC3474C2A, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x07881A0B, 0xC4C21CAB, },
	{ 0x0C7E4512, 0xC36775AD, },
	{ 0x1CD747DC, 0xBE03D832, },
	{ 0x27C0A714, 0xB1751B06, },
	{ 0x3199CF1C, 0x38527743, },
	{ 0x38CD3AB5, 0x4634C9DC, },
	{ 0x545CE0A8, 0x4B4CCE80, },
	{ 0x595C27FB, 0x8B1DD83A, },
	{ 0x6C305CB3, 0x41B0337B, },
	{ 0x76220E94, 0x48F1C4AD, },
	{ 0xA57CBE53, 0x0143E8A8, },
	{ 0xA9997109, 0x457FEBA9, },
	{ 0xB2C9B019, 0xDB97C70E, },
	{ 0xE5B3D348, 0x0AE8E549, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x4E5C5F26, 0x9BC5E33B, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xD4F6990D, 0xDAB6E612, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x264E8BED, 0x4B9554EB, },
	{ 0x2FA58122, 0x7CFD2733, },
	{ 0x58C59880, 0xD8633888, },
	{ 0xBA035FC8, 0x5D28A52B, },
};

// for 4.01 impose.prx 
static nid_entry sceImpose_driver_nid[] = {
	{ 0x531C9778, 0x6F502C0A, },
	{ 0x8C943191, 0x869EB4A8, },
	{ 0xB415FC59, 0xCD1291FD, },
};

resolver_config nid_fix_373_to_660[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceImpose_driver),
};

u32 nid_fix_373_to_660_size = NELEMS(nid_fix_373_to_660);
