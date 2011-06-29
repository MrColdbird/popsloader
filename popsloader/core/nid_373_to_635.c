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
	// for impose.prx
	{ 0x2F808748, 0x09DF9219, },
	{ 0x6373995D, 0x458A70B5, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x50F0C1EC, 0xE6BF3960, },
	{ 0x977DE386, 0xFFB9B760, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x6D302D3D, 0xFCD765C9, },
	// for impose.prx
	{ 0x62A27008, 0x8CE2AB86, },
	{ 0x659188E1, 0xEF9C9627, },
};

static nid_entry sceCtrl_driver_nid[] = {
	// for impose.prx
	{ 0x0B7AC633, 0x5D8CE0B2, },
	{ 0xC4AAD55F, 0x18654FC0, },
	{ 0xDB3CD94C, 0x33AB5BDB, },
	{ 0xDB6F93CB, 0x5B15473C, },
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

static nid_entry sceDisplay_driver_nid[] = {
	// for impose.prx
	{ 0x0E20F177, 0x0E20F177, },
	{ 0x32B67781, 0xD4EF6579, },
	{ 0x643F3841, 0xDF998667, },
	{ 0x906281D5, 0x73CA5F45, },
	{ 0x946155FD, 0xA70E2B3C, },
	{ 0x96CFAC38, 0x96CFAC38, },
	{ 0xDEA197D4, 0xDEA197D4, },
	{ 0xE55F0D50, 0xE55F0D50, },
};

static nid_entry sceRtc_driver_nid[] = {
	// for impose.prx
	{ 0x4DD19EAE, 0xF3B8D574, },
	{ 0x6A06446A, 0x0287B1C2, },
};

static nid_entry sceCodec_driver_nid[] = {
	// for impose.prx
	{ 0x1E4CC4C3, 0xD26B6CCE, },
	{ 0x261C6EE8, 0x261C6EE8, },
	{ 0x856E7487, 0x856E7487, },
};

static nid_entry scePower_driver_nid[] = {
	// for impose.prx
	{ 0x1BA2FCAE, 0x1BA2FCAE, },
	{ 0x3C5E45D8, 0xAB842949, },
	{ 0x54A35829, 0x81DCA5A5, },
	{ 0x78EC8DC9, 0xF36E1F37, },
	{ 0x86795186, 0xF8C9FAF5, },
	{ 0x9C98446E, 0x2CBFA597, },
	{ 0xA8D09A9A, 0x062CFDDC, },
	{ 0xC87DEC73, 0x57F6311D, },
	{ 0xE7A7ACE1, 0xDE18E7C0, },
};

static nid_entry sceReg_driver_nid[] = {
	// for impose.prx
	{ 0x0627AD6B, 0x7F17123E, },
	{ 0x1349B1B1, 0xA1671F90, },
	{ 0x1D4E8BC4, 0xA81437D0, },
	{ 0x53CB4B85, 0xBA1A6A86, },
	{ 0x8B5C6948, 0xA349B88E, },
	{ 0xA7C7B18E, 0x693B0D7F, },
	{ 0xCA3CEDE6, 0xAEF5B913, },
	{ 0xFC518070, 0x55C9A620, },
	{ 0xFDD753D1, 0x5476A667, },
};

static nid_entry sceHprm_driver_nid[] = {
	// for impose.prx
	{ 0x103DF40C, 0x0682085A, },
	{ 0x1528D408, 0xADE4B1F4, },
	{ 0x1910B327, 0x1910B327, },
	{ 0x7CC2B27E, 0xB05CD4A2, },
	{ 0xCFF04390, 0xF0A5DC5E, },
};

static nid_entry sceDve_driver_nid[] = {
	// for impose.prx
	{ 0x0B85524C, 0x9DAE67BC, },
	{ 0x93828323, 0x0DD3C1B4, },
	{ 0xA265B504, 0x1C67572C, },
};

static nid_entry KDebugForKernel_nid[] = {
	// for impose.prx
	{ 0xA216AE06, 0x92DA9CEF, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	// for impose.prx
	{ 0x8A389411, 0x359F6F5C, },
	{ 0xCA04A2B9, 0xCA04A2B9, },
};

resolver_config nid_fix_373_to_635[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceCtrl_driver),
	NID_ENTRY(sceDisplay_driver),
	NID_ENTRY(sceRtc_driver),
	NID_ENTRY(sceCodec_driver),
	NID_ENTRY(scePower_driver),
	NID_ENTRY(sceReg_driver),
	NID_ENTRY(sceHprm_driver),
	NID_ENTRY(sceDve_driver),
	NID_ENTRY(KDebugForKernel),
	NID_ENTRY(InterruptManagerForKernel),
};

u32 nid_fix_373_to_635_size = NELEMS(nid_fix_373_to_635);
