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
	// for impose.prx
	{ 0x4823B9D9, 0x458A70B5, },
	{ 0x9CCA041E, 0x09DF9219, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x24C5ABC2, 0xFFB9B760, },
	{ 0x63A3CAFB, 0xE6BF3960, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x63D88393, 0xFCD765C9, },
	// for impose.prx
	{ 0x2EAA8A5A, 0x8CE2AB86, },
	{ 0x6274D0D5, 0xEF9C9627, },
};

static nid_entry sceCtrl_driver_nid[] = {
	// for impose.prx
	{ 0x29A5082C, 0x5B15473C, },
	{ 0x591B3F36, 0x18654FC0, },
	{ 0xE3870772, 0x33AB5BDB, },
	{ 0xEB97D7AA, 0x5D8CE0B2, },
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

static nid_entry sceDisplay_driver_nid[] = {
	// for impose.prx
	{ 0x0E20F177, 0x0E20F177, },
	{ 0x2E6AA0AB, 0x73CA5F45, },
	{ 0x390C7E0E, 0xDF998667, },
	{ 0x6E57C773, 0x01F6B0D5, },
	{ 0x96CFAC38, 0x96CFAC38, },
	{ 0xDB98F049, 0xD4EF6579, },
	{ 0xDEA197D4, 0xDEA197D4, },
	{ 0xE55F0D50, 0xE55F0D50, },
	{ 0xEB6C2BA3, 0xA70E2B3C, },
};

static nid_entry sceRtc_driver_nid[] = {
	// for impose.prx
	{ 0x1D90BCF2, 0x0287B1C2, },
	{ 0x8EB1DEAC, 0xF3B8D574, },
};

static nid_entry sceCodec_driver_nid[] = {
	// for impose.prx
	{ 0x073DE131, 0xD26B6CCE, },
	{ 0x261C6EE8, 0x261C6EE8, },
	{ 0x856E7487, 0x856E7487, },
};

static nid_entry scePower_driver_nid[] = {
	// for impose.prx
	{ 0x1BA2FCAE, 0x1BA2FCAE, },
	{ 0x45BB59FE, 0xDE18E7C0, },
	{ 0x56083981, 0xF36E1F37, },
	{ 0xAC664491, 0x2CBFA597, },
	{ 0xC35907C2, 0x57F6311D, },
	{ 0xC6D21BB6, 0xF8C9FAF5, },
	{ 0xCF0F53E5, 0x062CFDDC, },
	{ 0xD61C63BD, 0xAB842949, },
	{ 0xFBFD57EB, 0x81DCA5A5, },
};

static nid_entry sceReg_driver_nid[] = {
	// for impose.prx
	{ 0x24DDA193, 0xA349B88E, },
	{ 0x3273A94B, 0xAEF5B913, },
	{ 0x636D5C60, 0xA81437D0, },
	{ 0x9943E18A, 0x55C9A620, },
	{ 0x9C756292, 0xBA1A6A86, },
	{ 0xB8FD8784, 0x5476A667, },
	{ 0xCDC72B4D, 0x693B0D7F, },
	{ 0xD3CD942D, 0xA1671F90, },
	{ 0xE4D4F126, 0x7F17123E, },
};

static nid_entry sceHprm_driver_nid[] = {
	// for impose.prx
	{ 0x1910B327, 0x1910B327, },
	{ 0x3459F450, 0x8F2559DE, },
	{ 0x3709DC86, 0x4C1F35A1, },
	{ 0x404D9DE4, 0xADE4B1F4, },
	{ 0x71E989F4, 0x73587D56, },
	{ 0xAE42F741, 0xA971659D, },
	{ 0xCA90EB48, 0xB05CD4A2, },
	{ 0xE5AB910C, 0x38FB84B5, },
	{ 0xF7FA0802, 0x0682085A, },
};

static nid_entry sceDve_driver_nid[] = {
	// for impose.prx
	{ 0x738FE169, 0x9DAE67BC, },
	{ 0x89CCB808, 0x1C67572C, },
	{ 0xC597DDDD, 0x0DD3C1B4, },
};

static nid_entry KDebugForKernel_nid[] = {
	// for impose.prx
	{ 0x59E95C49, 0x92DA9CEF, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	// for impose.prx
	{ 0x169FC5A3, 0x359F6F5C, },
	{ 0xB940A5BF, 0xD06AA711, },
};

static nid_entry InitForKernel_nid[] = {
	// for impose.prx
	{ 0x6289D9A1, 0x2213275D, }
};

resolver_config nid_fix_400_to_635[] = {
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
	NID_ENTRY(InitForKernel),
};

u32 nid_fix_400_to_635_size = NELEMS(nid_fix_400_to_635);
