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
	{ 0x2CFF6F90, 0xB4F00CB5, },
	{ 0x5339A163, 0xFDC97D28, },
	{ 0x950BCB31, 0xF12A62F7, },
	{ 0xD7E24299, 0x9F205D3E, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0xBB8C8FDF, 0x3FF74DF1, },
	{ 0xC5A281C5, 0x939E4270, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x9C9BB2D8, 0xC3474C2A, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x0BBCA0BF, 0x0F067E16, },
	{ 0xA516434B, 0x5557F4E2, },
	{ 0xDA315C59, 0x28B97035, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x08E0EE7E, 0x38527743, },
	{ 0x0E6301D0, 0xDB97C70E, },
	{ 0x20C9E2C4, 0x457FEBA9, },
	{ 0x410C74F7, 0x4634C9DC, },
	{ 0x461B8077, 0x0143E8A8, },
	{ 0x48869494, 0x41B0337B, },
	{ 0x5F190A4E, 0x48F1C4AD, },
	{ 0x663D5471, 0x0AE8E549, },
	{ 0x7A154A45, 0xBE03D832, },
	{ 0x823FFD7A, 0xB1751B06, },
	{ 0x923509A1, 0xC36775AD, },
	{ 0xC7FC7669, 0x8B1DD83A, },
	{ 0xE46A0890, 0x4B4CCE80, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x48728250, 0x9BC5E33B, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xD1A8E10E, 0xDAB6E612, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x0C9C3686, 0xAFE6C9EF, },
	{ 0x1F226BA9, 0xD8633888, },
	{ 0x6663F1BD, 0x5D28A52B, },
	{ 0x6849A0B0, 0x4B9554EB, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x10B1710B, 0xE97E9718, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0xF5DBC7AA, 0xB2BEADB8, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x0CC96C20, 0x48005974, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0xA48DE786, 0x376399B6, },
};

resolver_config nid_fix_500_to_660[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceDisplay_driver),
	NID_ENTRY(sceHprm_driver),
	NID_ENTRY(sceDve_driver),
	NID_ENTRY(sceCodec_driver),
};

u32 nid_fix_500_to_660_size = NELEMS(nid_fix_500_to_660);
