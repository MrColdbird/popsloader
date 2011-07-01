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
	{ 0x9D9A5BA1, 0xFEB5C72B, },
	{ 0xCDA3A2F7, 0xA4AC3934, },
	{ 0xCF4DE78C, 0xF5780DAA, },
	{ 0xFC114573, 0xB9796F69, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x50F0C1EC, 0xDF8FFFAB, },
	{ 0x977DE386, 0xE3CCC6EA, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x6D302D3D, 0x29413885, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x07881A0B, 0x774775CA, },
	{ 0x0C7E4512, 0x9EBB3C43, },
	{ 0x1CD747DC, 0x34EED467, },
	{ 0x27C0A714, 0xB733A263, },
	{ 0x3199CF1C, 0x2B3BE2C8, },
	{ 0x38CD3AB5, 0x5D3DD0B3, },
	{ 0x545CE0A8, 0x94914740, },
	{ 0x595C27FB, 0xE7849809, },
	{ 0x6C305CB3, 0x47966D28, },
	{ 0x76220E94, 0x2D858336, },
	{ 0xA57CBE53, 0x4643F826, },
	{ 0xA9997109, 0x97EA6913, },
	{ 0xB2C9B019, 0x314A489C, },
	{ 0xE5B3D348, 0x119647A7, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x4E5C5F26, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xD4F6990D, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x264E8BED, 0x23E9F5FA, },
	{ 0x2FA58122, 0x862248FD, },
	{ 0x58C59880, 0xD4D665C9, },
	{ 0xBA035FC8, 0xF489E74B, },
};

// for 4.01 impose.prx 
static nid_entry sceImpose_driver_nid[] = {
	{ 0x531C9778, 0x6F502C0A, },
	{ 0x8C943191, 0x869EB4A8, },
	{ 0xB415FC59, 0xCD1291FD, },
};

resolver_config nid_fix_373_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceImpose_driver),
};

u32 nid_fix_373_to_620_size = NELEMS(nid_fix_373_to_620);
