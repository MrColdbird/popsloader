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
	{ 0x4823B9D9, 0x07C586A1, },
	{ 0x9CCA041E, 0x22A114DC, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x2EAA8A5A, 0x1F08547A, },
	{ 0x6274D0D5, 0xB57D0DEC, },
};

static nid_entry sceCtrl_driver_nid[] = {
	{ 0x29A5082C, 0xF8346777, },
	{ 0x591B3F36, 0x2BA616AF, },
	{ 0xE3870772, 0x1809B9FC, },
	{ 0xEB97D7AA, 0xDF53E160, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x0E20F177, 0x0E20F177, },
	{ 0x2E6AA0AB, 0x3552AB11, },
	{ 0x390C7E0E, 0x3E17FE8D, },
	{ 0x6E57C773, 0x996881D2, },
	{ 0x96CFAC38, 0x96CFAC38, },
	{ 0xDB98F049, 0x33B620AF, },
	{ 0xDEA197D4, 0xDEA197D4, },
	{ 0xE55F0D50, 0xE55F0D50, },
	{ 0xEB6C2BA3, 0x117C3E2C, },
};

static nid_entry sceRtc_driver_nid[] = {
	{ 0x1D90BCF2, 0x9012B140, },
	{ 0x8EB1DEAC, 0xDFF30673, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0x073DE131, 0xE4456BC3, },
	{ 0x261C6EE8, 0x261C6EE8, },
	{ 0x856E7487, 0x856E7487, },
};

static nid_entry scePower_driver_nid[] = {
	{ 0x1BA2FCAE, 0x1BA2FCAE, },
	{ 0x45BB59FE, 0xFA651CE1, },
	{ 0x56083981, 0x88C79735, },
	{ 0xAC664491, 0x31AEA94C, },
	{ 0xC35907C2, 0x2509FF3B, },
	{ 0xC6D21BB6, 0x872F4ECE, },
	{ 0xCF0F53E5, 0x5C1333B7, },
	{ 0xD61C63BD, 0x7A9EA6DE, },
	{ 0xFBFD57EB, 0x8C873AA7, },
};

static nid_entry sceReg_driver_nid[] = {
	{ 0x24DDA193, 0x49D77D65, },
	{ 0x3273A94B, 0x5FD4764A, },
	{ 0x636D5C60, 0x9980519F, },
	{ 0x9943E18A, 0xD743A608, },
	{ 0x9C756292, 0x4F471457, },
	{ 0xB8FD8784, 0x49C70163, },
	{ 0xCDC72B4D, 0xF4A3E396, },
	{ 0xD3CD942D, 0xFC742751, },
	{ 0xE4D4F126, 0xDBA46704, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0x1910B327, 0x1910B327, },
	{ 0x3459F450, 0xFA4A25A7, },
	{ 0x3709DC86, 0x8AEC8EE9, },
	{ 0x404D9DE4, 0xB2BEADB8, },
	{ 0x71E989F4, 0x0B83352B, },
	{ 0xAE42F741, 0x8C728BB4, },
	{ 0xCA90EB48, 0x370DDC12, },
	{ 0xE5AB910C, 0x301063CC, },
	{ 0xF7FA0802, 0xEFCFD0C5, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x738FE169, 0xED631526, },
	{ 0x89CCB808, 0x253B69B6, },
	{ 0xC597DDDD, 0x77832653, },
};

static nid_entry KDebugForKernel_nid[] = {
	{ 0x59E95C49, 0xB41E2430, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	{ 0x169FC5A3, 0x4023E1A7, },
	{ 0xB940A5BF, 0xFFA8B183, },
};

static nid_entry InitForKernel_nid[] = {
	{ 0x6289D9A1, 0xA18A4A8B, },
};

resolver_config nid_impose_fix_400_to_660[] = {
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

u32 nid_impose_fix_400_to_660_size = NELEMS(nid_impose_fix_400_to_660);
