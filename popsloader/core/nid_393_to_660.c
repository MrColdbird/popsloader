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
	{ 0x539F8A51, 0xFDC97D28, },
	{ 0x9110439F, 0xB4F00CB5, },
	{ 0xBC3AFFF2, 0xF12A62F7, },
	{ 0xE151223E, 0x9F205D3E, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x1D313DE9, 0x3FF74DF1, },
	{ 0xAE802E8F, 0x939E4270, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xAE5AC5D3, 0xC3474C2A, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x0A0F9644, 0x38527743, },
	{ 0x0F8D83B8, 0xC36775AD, },
	{ 0x26A0937D, 0x457FEBA9, },
	{ 0x31D046A0, 0xC4C21CAB, },
	{ 0x33E54489, 0x0143E8A8, },
	{ 0x418CCE8D, 0x41B0337B, },
	{ 0x49F7F222, 0x48F1C4AD, },
	{ 0x7AC62361, 0x4634C9DC, },
	{ 0xA837DCEB, 0x4B4CCE80, },
	{ 0xB87B15D4, 0x0AE8E549, },
	{ 0xD040B7AB, 0xDB97C70E, },
	{ 0xD3CD4CC8, 0x8B1DD83A, },
	{ 0xEE11D026, 0xBE03D832, },
	{ 0xF8623D08, 0xB1751B06, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0xAE31405A, 0x9BC5E33B, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x87CEDE80, 0xDAB6E612, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x0C15B44A, 0xD8633888, },
	{ 0x4659CC7C, 0xAFE6C9EF, },
	{ 0x7008C80C, 0x4B9554EB, },
	{ 0x8B2CE4CE, 0x5D28A52B, },
	{ 0xB267CB88, 0x7CFD2733, },
};

// for 4.01 impose.prx 
static nid_entry sceImpose_driver_nid[] = {
	{ 0x21D3EA22, 0x6F502C0A, },
	{ 0xD4FDA428, 0xCD1291FD, },
	{ 0xFC9B1843, 0x869EB4A8, },
};

resolver_config nid_fix_393_to_660[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
};

u32 nid_fix_393_to_660_size = NELEMS(nid_fix_393_to_660);
