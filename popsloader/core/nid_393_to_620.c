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
	{ 0x539F8A51, 0xA4AC3934, },
	{ 0x9110439F, 0xB9796F69, },
	{ 0xBC3AFFF2, 0xFEB5C72B, },
	{ 0xE151223E, 0xF5780DAA, },
	// for impose.prx
	{ 0xA3B0B6BC, 0x864EBFD7, },
	{ 0xF75BE1B2, 0x18D7F644, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x1D313DE9, 0xDF8FFFAB, },
	{ 0xAE802E8F, 0xE3CCC6EA, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xAE5AC5D3, 0x29413885, },
	// for impose.prx
	{ 0x753EF37C, 0xB848CC2C, },
	{ 0x860783BF, 0x63BB2F2C, },
};

static nid_entry sceCtrl_driver_nid[] = {
	// for impose.prx
	{ 0x02DC2E6C, 0xEB6CDD17, },
	{ 0x270345D5, 0xF3132A07, },
	{ 0xC2D874D7, 0x063D8197, },
	{ 0xD65D4E9A, 0x3CA6922B, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x0A0F9644, 0xEF64EFDD, },
	{ 0x0F8D83B8, 0x9EBB3C43, },
	{ 0x26A0937D, 0x97EA6913, },
	{ 0x31D046A0, 0x774775CA, },
	{ 0x33E54489, 0xF6922705, },
	{ 0x418CCE8D, 0x47966D28, },
	{ 0x49F7F222, 0x2D858336, },
	{ 0x7AC62361, 0x5D3DD0B3, },
	{ 0xA837DCEB, 0x94914740, },
	{ 0xB87B15D4, 0x119647A7, },
	{ 0xD040B7AB, 0x314A489C, },
	{ 0xD3CD4CC8, 0xE7849809, },
	{ 0xEE11D026, 0x34EED467, },
	{ 0xF8623D08, 0xB733A263, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0xAE31405A, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x87CEDE80, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x0C15B44A, 0xD4D665C9, },
	{ 0x4659CC7C, 0x7E2381D2, },
	{ 0x7008C80C, 0x23E9F5FA, },
	{ 0x8B2CE4CE, 0xF489E74B, },
	{ 0xB267CB88, 0x862248FD, },
};

static nid_entry sceDisplay_driver_nid[] = {
	// for impose.prx
	{ 0x0E20F177, 0x0E20F177, },
	{ 0x1A4E0C25, 0x2A1826A2, },
	{ 0x7E67BFCF, 0xA20A245E, },
	{ 0x96CFAC38, 0x96CFAC38, },
	{ 0xB0D487B3, 0xC7161CF7, },
	{ 0xBE25CDE5, 0xDC68E0EF, },
	{ 0xDEA197D4, 0xDEA197D4, },
	{ 0xE55F0D50, 0xE55F0D50, },
	{ 0xF5EEEFEF, 0x6C42016A, },
};

static nid_entry sceRtc_driver_nid[] = {
	// for impose.prx
	{ 0x11AAB2A0, 0xCFBE4A68, },
	{ 0xA19F9CEB, 0xA0B3BF0F, },
};

static nid_entry sceCodec_driver_nid[] = {
	// for impose.prx
	{ 0x261C6EE8, 0x261C6EE8, },
	{ 0x7509BB52, 0xBCE58DC4, },
	{ 0x856E7487, 0x856E7487, },
};

static nid_entry scePower_driver_nid[] = {
	{ 0xEBD177D6, 0xEBD177D6, },
	// for impose.prx
	{ 0x0C4922CF, 0x5202A826, },
	{ 0x1BA2FCAE, 0x1BA2FCAE, },
	{ 0x28764591, 0x9E09D19B, },
	{ 0x30D2EE6D, 0x279492B3, },
	{ 0x9FC87DE9, 0xBC8823E8, },
	{ 0xAC3E6CCF, 0x7F480684, },
	{ 0xE1837FC2, 0xC9885394, },
	{ 0xE8F681DB, 0xE5F8596E, },
	{ 0xED21B8EF, 0x4084E678, },
};

static nid_entry sceReg_driver_nid[] = {
	// for impose.prx
	{ 0x046EEC93, 0xF3300EBF, },
	{ 0x178B7336, 0x8A0F5133, },
	{ 0x1E75765A, 0x0404652C, },
	{ 0x715ACB63, 0x21928F15, },
	{ 0x90CEE4CD, 0x31F9DB91, },
	{ 0x98472F48, 0xDC7EF81C, },
	{ 0xD0A0DEDB, 0x08BEB24C, },
	{ 0xD58C391F, 0x400BB753, },
	{ 0xF77FE5D5, 0x873EB4E1, },
};

static nid_entry sceHprm_driver_nid[] = {
	// for impose.prx
	{ 0x11941056, 0x2E49469C, },
	{ 0x1910B327, 0x1910B327, },
	{ 0x7B1A14B8, 0x2F028F97, },
	{ 0x7FA77FBD, 0x4C9BEDA4, },
	{ 0x9975BBAE, 0x8A898B38, },
	{ 0x9C1D9ADB, 0xDA01152D, },
	{ 0x9D148F75, 0x1EECCA1A, },
	{ 0xA742948B, 0x62CDFB12, },
	{ 0xD691F551, 0x732EC325, },
};

static nid_entry sceDve_driver_nid[] = {
	// for impose.prx
	{ 0x1570A055, 0x2F863B65, },
	{ 0x4493159A, 0x024D7064, },
	{ 0x4E94688B, 0x194FE107, },
};

static nid_entry KDebugForKernel_nid[] = {
	// for impose.prx
	{ 0xEF30654A, 0xD9DB4F02, },
};

static nid_entry InterruptManagerForKernel_nid[] = {
	// for impose.prx
	{ 0x9A265F8C, 0x3C161DFB, },
	{ 0x9A81B995, 0xC03C8D51, },
};

static nid_entry InitForKernel_nid[] = {
	// for impose.prx
	{ 0xEF8678B9, 0x29DAA63F, },
};

resolver_config nid_fix_393_to_620[] = {
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

u32 nid_fix_393_to_620_size = NELEMS(nid_fix_393_to_620);
