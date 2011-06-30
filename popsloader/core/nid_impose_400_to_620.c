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
	{ 0x4823B9D9, 0x864EBFD7, },
	{ 0x9CCA041E, 0x18D7F644, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x2EAA8A5A, 0x63BB2F2C, },
	{ 0x6274D0D5, 0xB848CC2C, },
};

static nid_entry sceCtrl_driver_nid[] = {
	{ 0x29A5082C, 0xF3132A07, },
	{ 0x591B3F36, 0x3CA6922B, },
	{ 0xE3870772, 0x063D8197, },
	{ 0xEB97D7AA, 0xEB6CDD17, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x0E20F177, 0x0E20F177, },
	{ 0x2E6AA0AB, 0xC7161CF7, },
	{ 0x390C7E0E, 0xDC68E0EF, },
	{ 0x6E57C773, 0x6C42016A, },
	{ 0x96CFAC38, 0x96CFAC38, },
	{ 0xDB98F049, 0x2A1826A2, },
	{ 0xDEA197D4, 0xDEA197D4, },
	{ 0xE55F0D50, 0xE55F0D50, },
	{ 0xEB6C2BA3, 0xA20A245E, },
};

static nid_entry sceRtc_driver_nid[] = {
	{ 0x1D90BCF2, 0xA0B3BF0F, },
	{ 0x8EB1DEAC, 0xCFBE4A68, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0x073DE131, 0xBCE58DC4, },
	{ 0x261C6EE8, 0x261C6EE8, },
	{ 0x856E7487, 0x856E7487, },
};

static nid_entry scePower_driver_nid[] = {
	{ 0x1BA2FCAE, 0x1BA2FCAE, },
	{ 0x45BB59FE, 0x279492B3, },
	{ 0x56083981, 0x9E09D19B, },
	{ 0xAC664491, 0xE5F8596E, },
	{ 0xC35907C2, 0x4084E678, },
	{ 0xC6D21BB6, 0x7F480684, },
	{ 0xCF0F53E5, 0xC9885394, },
	{ 0xD61C63BD, 0x5202A826, },
	{ 0xFBFD57EB, 0xBC8823E8, },
};

static nid_entry sceReg_driver_nid[] = {
	{ 0x24DDA193, 0xF3300EBF, },
	{ 0x3273A94B, 0x31F9DB91, },
	{ 0x636D5C60, 0x400BB753, },
	{ 0x9943E18A, 0x0404652C, },
	{ 0x9C756292, 0x8A0F5133, },
	{ 0xB8FD8784, 0xDC7EF81C, },
	{ 0xCDC72B4D, 0x08BEB24C, },
	{ 0xD3CD942D, 0x21928F15, },
	{ 0xE4D4F126, 0x873EB4E1, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0x1910B327, 0x1910B327, },
	{ 0x3459F450, 0x2E49469C, },
	{ 0x3709DC86, 0x1EECCA1A, },
	{ 0x404D9DE4, 0x62CDFB12, },
	{ 0x71E989F4, 0x732EC325, },
	{ 0xAE42F741, 0x2F028F97, },
	{ 0xCA90EB48, 0x8A898B38, },
	{ 0xE5AB910C, 0xDA01152D, },
	{ 0xF7FA0802, 0x4C9BEDA4, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x738FE169, 0x194FE107, },
	{ 0x89CCB808, 0x024D7064, },
	{ 0xC597DDDD, 0x2F863B65, },
};

static nid_entry KDebugForKernel_nid[] = {
	{ 0x59E95C49, 0xD9DB4F02, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	{ 0x169FC5A3, 0xC03C8D51, },
	{ 0xB940A5BF, 0x3C161DFB, },
};

static nid_entry InitForKernel_nid[] = {
	{ 0x6289D9A1, 0x29DAA63F, }
};

resolver_config nid_impose_fix_400_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(LoadExecForKernel),
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
	NID_ENTRY(InitForKernel),
};

u32 nid_impose_fix_400_to_620_size = NELEMS(nid_impose_fix_400_to_620);
