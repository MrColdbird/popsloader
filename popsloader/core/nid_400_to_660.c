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
	{ 0x12720EDA, 0xB4F00CB5, },
	{ 0x3EEE43C5, 0xFDC97D28, },
	{ 0x5136926D, 0xF12A62F7, },
	{ 0x523E300A, 0xC90B0992 , },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x24C5ABC2, 0x939E4270, },
	{ 0x63A3CAFB, 0x3FF74DF1, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x63D88393, 0xC3474C2A, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x15574362, 0xC36775AD, },
	{ 0x21797DCF, 0x4B4CCE80, },
	{ 0x23D205CA, 0xC4C21CAB, },
	{ 0x643169E5, 0x8B1DD83A, },
	{ 0x67583EF1, 0xB1751B06, },
	{ 0x88E26FBC, 0xBE03D832, },
	{ 0x8E6586AD, 0x48F1C4AD, },
	{ 0xA36C4E9E, 0x457FEBA9, },
	{ 0xB60FBA15, 0x38527743, },
	{ 0xC4B60AB3, 0x41B0337B, },
	{ 0xD80E8AAF, 0x0AE8E549, },
	{ 0xD83733C9, 0x0143E8A8, },
	{ 0xE08034E0, 0x4634C9DC, },
	{ 0xE65B0490, 0xDB97C70E, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x581D72B2, 0x9BC5E33B, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0x17FA615B, 0xDAB6E612, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x1DDA69CE, 0xD8633888, },
	{ 0xA402A161, 0x4B9554EB, },
	{ 0xC545B81E, 0x7CFD2733, },
	{ 0xDC09D302, 0xAFE6C9EF, },
	{ 0xF5423CAA, 0x5D28A52B, },
};

resolver_config nid_fix_400_to_660[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
};

u32 nid_fix_400_to_660_size = NELEMS(nid_fix_400_to_660);
