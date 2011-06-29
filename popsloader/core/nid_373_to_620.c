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
	// for impose.prx
	{ 0x2F808748, 0x8D34BBDA, },
	{ 0x6373995D, 0x864EBFD7, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x50F0C1EC, 0xDF8FFFAB, },
	{ 0x977DE386, 0xE3CCC6EA, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x6D302D3D, 0x29413885, },
	// for impose.prx
	{ 0x62A27008, 0x63BB2F2C, },
	{ 0x659188E1, 0xB848CC2C, },
};

static nid_entry sceCtrl_driver_nid[] = {
	// for impose.prx
	{ 0x0B7AC633, UNKNOWNNID, },
	{ 0xC4AAD55F, 0x3CA6922B, },
	{ 0xDB3CD94C, UNKNOWNNID, },
	{ 0xDB6F93CB, UNKNOWNNID, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x07881A0B, 0x774775CA, },
	{ 0x0C7E4512, UNKNOWNNID, },
	{ 0x1CD747DC, UNKNOWNNID, },
	{ 0x27C0A714, UNKNOWNNID, },
	{ 0x3199CF1C, 0x2B3BE2C8, },
	{ 0x38CD3AB5, UNKNOWNNID, },
	{ 0x545CE0A8, UNKNOWNNID, },
	{ 0x595C27FB, UNKNOWNNID, },
	{ 0x6C305CB3, UNKNOWNNID, },
	{ 0x76220E94, 0x2D858336, },
	{ 0xA57CBE53, UNKNOWNNID, },
	{ 0xA9997109, 0x97EA6913, },
	{ 0xB2C9B019, UNKNOWNNID, },
	{ 0xE5B3D348, UNKNOWNNID, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x4E5C5F26, UNKNOWNNID, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xD4F6990D, UNKNOWNNID, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x264E8BED, UNKNOWNNID, },
	{ 0x2FA58122, UNKNOWNNID, },
	{ 0x58C59880, UNKNOWNNID, },
	{ 0xBA035FC8, UNKNOWNNID, },
};

static nid_entry sceDisplay_driver_nid[] = {
	// for impose.prx
	{ 0x0E20F177, UNKNOWNNID, },
	{ 0x32B67781, UNKNOWNNID, },
	{ 0x643F3841, UNKNOWNNID, },
	{ 0x906281D5, UNKNOWNNID, },
	{ 0x946155FD, UNKNOWNNID, },
	{ 0x96CFAC38, UNKNOWNNID, },
	{ 0xDEA197D4, UNKNOWNNID, },
	{ 0xE55F0D50, UNKNOWNNID, },
};

static nid_entry sceRtc_driver_nid[] = {
	// for impose.prx
	{ 0x4DD19EAE, UNKNOWNNID, },
	{ 0x6A06446A, UNKNOWNNID, },
};

static nid_entry sceCodec_driver_nid[] = {
	// for impose.prx
	{ 0x1E4CC4C3, UNKNOWNNID, },
	{ 0x261C6EE8, UNKNOWNNID, },
	{ 0x856E7487, UNKNOWNNID, },
};

static nid_entry scePower_driver_nid[] = {
	// for impose.prx
	{ 0x1BA2FCAE, UNKNOWNNID, },
	{ 0x3C5E45D8, UNKNOWNNID, },
	{ 0x54A35829, UNKNOWNNID, },
	{ 0x78EC8DC9, UNKNOWNNID, },
	{ 0x86795186, UNKNOWNNID, },
	{ 0x9C98446E, UNKNOWNNID, },
	{ 0xA8D09A9A, UNKNOWNNID, },
	{ 0xC87DEC73, UNKNOWNNID, },
	{ 0xE7A7ACE1, UNKNOWNNID, },
};

static nid_entry sceReg_driver_nid[] = {
	// for impose.prx
	{ 0x0627AD6B, UNKNOWNNID, },
	{ 0x1349B1B1, UNKNOWNNID, },
	{ 0x1D4E8BC4, UNKNOWNNID, },
	{ 0x53CB4B85, UNKNOWNNID, },
	{ 0x8B5C6948, UNKNOWNNID, },
	{ 0xA7C7B18E, UNKNOWNNID, },
	{ 0xCA3CEDE6, UNKNOWNNID, },
	{ 0xFC518070, UNKNOWNNID, },
	{ 0xFDD753D1, UNKNOWNNID, },
};

static nid_entry sceHprm_driver_nid[] = {
	// for impose.prx
	{ 0x103DF40C, UNKNOWNNID, },
	{ 0x1528D408, 0x61650073, },
	{ 0x1910B327, UNKNOWNNID, },
	{ 0x7CC2B27E, UNKNOWNNID, },
	{ 0xCFF04390, UNKNOWNNID, },
};

static nid_entry sceDve_driver_nid[] = {
	// for impose.prx
	{ 0x0B85524C, 0x194FE107, },
	{ 0x93828323, 0x2F863B65, },
	{ 0xA265B504, 0x024D7064, },
};

static nid_entry KDebugForKernel_nid[] = {
	// for impose.prx
	{ 0xA216AE06, 0xD9DB4F02, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	// for impose.prx
	{ 0x8A389411, 0xC03C8D51, },
	{ 0xCA04A2B9, 0x3C161DFB, },
};

resolver_config nid_fix_373_to_620[] = {
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

u32 nid_fix_373_to_620_size = NELEMS(nid_fix_373_to_620);
