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
	// for impose.prx
	{ 0xA3B0B6BC, 0x458A70B5, },
	{ 0xF75BE1B2, 0x09DF9219, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x1D313DE9, 0xE6BF3960, },
	{ 0xAE802E8F, 0xFFB9B760, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xAE5AC5D3, 0xFCD765C9, },
	// for impose.prx
	{ 0x753EF37C, 0xEF9C9627, },
	{ 0x860783BF, 0x8CE2AB86, },
};

static nid_entry sceCtrl_driver_nid[] = {
	// for impose.prx
	{ 0x02DC2E6C, 0x5D8CE0B2, },
	{ 0x270345D5, 0x5B15473C, },
	{ 0xC2D874D7, 0x33AB5BDB, },
	{ 0xD65D4E9A, 0x18654FC0, },
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

static nid_entry sceDisplay_driver_nid[] = {
	// for impose.prx
	{ 0x0E20F177, 0x0E20F177, },
	{ 0x1A4E0C25, 0xD4EF6579, },
	{ 0x7E67BFCF, 0xA70E2B3C, },
	{ 0x96CFAC38, 0x96CFAC38, },
	{ 0xB0D487B3, 0x73CA5F45, },
	{ 0xBE25CDE5, 0xDF998667, },
	{ 0xDEA197D4, 0xDEA197D4, },
	{ 0xE55F0D50, 0xE55F0D50, },
	{ 0xF5EEEFEF, 0x01F6B0D5, },
};

static nid_entry sceRtc_driver_nid[] = {
	// for impose.prx
	{ 0x11AAB2A0, 0xF3B8D574, },
	{ 0xA19F9CEB, 0x0287B1C2, },
};

static nid_entry sceCodec_driver_nid[] = {
	// for impose.prx
	{ 0x261C6EE8, 0x261C6EE8, },
	{ 0x7509BB52, 0xD26B6CCE, },
	{ 0x856E7487, 0x856E7487, },
};

static nid_entry scePower_driver_nid[] = {
	{ 0xEBD177D6, 0xEBD177D6, },
	// for impose.prx
	{ 0x0C4922CF, 0xAB842949, },
	{ 0x1BA2FCAE, 0x1BA2FCAE, },
	{ 0x28764591, 0xF36E1F37, },
	{ 0x30D2EE6D, 0xDE18E7C0, },
	{ 0x9FC87DE9, 0x81DCA5A5, },
	{ 0xAC3E6CCF, 0xF8C9FAF5, },
	{ 0xE1837FC2, 0x062CFDDC, },
	{ 0xE8F681DB, 0x2CBFA597, },
	{ 0xED21B8EF, 0x57F6311D, },
};

static nid_entry sceReg_driver_nid[] = {
	// for impose.prx
	{ 0x046EEC93, 0xA349B88E, },
	{ 0x178B7336, 0xBA1A6A86, },
	{ 0x1E75765A, 0x55C9A620, },
	{ 0x715ACB63, 0xA1671F90, },
	{ 0x90CEE4CD, 0xAEF5B913, },
	{ 0x98472F48, 0x5476A667, },
	{ 0xD0A0DEDB, 0x693B0D7F, },
	{ 0xD58C391F, 0xA81437D0, },
	{ 0xF77FE5D5, 0x7F17123E, },
};

static nid_entry sceHprm_driver_nid[] = {
	// for impose.prx
	{ 0x11941056, 0x8F2559DE, },
	{ 0x1910B327, 0x1910B327, },
	{ 0x7B1A14B8, 0xA971659D, },
	{ 0x7FA77FBD, 0x0682085A, },
	{ 0x9975BBAE, 0xB05CD4A2, },
	{ 0x9C1D9ADB, 0x38FB84B5, },
	{ 0x9D148F75, 0x4C1F35A1, },
	{ 0xA742948B, 0xADE4B1F4, },
	{ 0xD691F551, 0x73587D56, },
};

static nid_entry sceDve_driver_nid[] = {
	// for impose.prx
	{ 0x1570A055, 0x0DD3C1B4, },
	{ 0x4493159A, 0x1C67572C, },
	{ 0x4E94688B, 0x9DAE67BC, },
};

static nid_entry KDebugForKernel_nid[] = {
	// for impose.prx
	{ 0xEF30654A, 0x92DA9CEF, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	// for impose.prx
	{ 0x9A265F8C, 0xD06AA711, },
	{ 0x9A81B995, 0x359F6F5C, },
};

static nid_entry InitForKernel_nid[] = {
	// for impose.prx
	{ 0xEF8678B9, 0x2213275D, },
};

resolver_config nid_fix_393_to_635[] = {
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

u32 nid_fix_393_to_635_size = NELEMS(nid_fix_393_to_635);
