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
	{ 0x07C586A1, UNKNOWNNID, },
	{ 0x310802A9, UNKNOWNNID, },
	{ 0x8AE776AF, UNKNOWNNID, },
	{ 0xB4F00CB5, UNKNOWNNID, },
	{ 0xC90B0992, UNKNOWNNID, },
	{ 0xF12A62F7, UNKNOWNNID, },
	{ 0xFDC97D28, UNKNOWNNID, },
};

static nid_entry InitForKernel_nid[] = {
	{ 0x9D33A110, UNKNOWNNID, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x3FF74DF1, UNKNOWNNID, },
	{ 0x939E4270, UNKNOWNNID, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xC3474C2A, UNKNOWNNID, },
};

static nid_entry sceRtc_driver_nid[] = {
	{ 0x4E267E02, UNKNOWNNID, },
	{ 0xE7B3ABF4, UNKNOWNNID, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x0F067E16, UNKNOWNNID, },
	{ 0x133DB99A, UNKNOWNNID, },
	{ 0x28B97035, UNKNOWNNID, },
	{ 0x5557F4E2, UNKNOWNNID, },
	{ 0xB497314D, UNKNOWNNID, },
	{ 0xDC3BECFF, UNKNOWNNID, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x0AE8E549, UNKNOWNNID, },
	{ 0x38527743, UNKNOWNNID, },
	{ 0x41B0337B, UNKNOWNNID, },
	{ 0x457FEBA9, UNKNOWNNID, },
	{ 0x4634C9DC, UNKNOWNNID, },
	{ 0x48F1C4AD, UNKNOWNNID, },
	{ 0x4B4CCE80, UNKNOWNNID, },
	{ 0x8B1DD83A, UNKNOWNNID, },
	{ 0xB1751B06, UNKNOWNNID, },
	{ 0xC36775AD, UNKNOWNNID, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x48448373, UNKNOWNNID, },
	{ 0x9BC5E33B, UNKNOWNNID, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xDAB6E612, UNKNOWNNID, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x4B9554EB, UNKNOWNNID, },
	{ 0x5D28A52B, UNKNOWNNID, },
	{ 0xAFE6C9EF, UNKNOWNNID, },
	{ 0xD8633888, UNKNOWNNID, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x03F16FD4, UNKNOWNNID, },
	{ 0xE38CA615, UNKNOWNNID, },
	{ 0xE97E9718, UNKNOWNNID, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0xB2BEADB8, UNKNOWNNID, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x48005974, UNKNOWNNID, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0x376399B6, UNKNOWNNID, },
};

static nid_entry sceCtrl_driver_nid[] = {
	{ 0x6C86AF22, UNKNOWNNID, },
};

static nid_entry scePadSvc_driver_nid[] = {
	{ 0x05C9C803, UNKNOWNNID, },
	{ 0x0B3E6FD3, UNKNOWNNID, },
	{ 0x7CAB5A3D, UNKNOWNNID, },
};

resolver_config nid_fix_660_to_620[] = {
	NID_ENTRY(SysMemForKernel),
	NID_ENTRY(InitForKernel),
	NID_ENTRY(ModuleMgrForKernel),
	NID_ENTRY(LoadExecForKernel),
	NID_ENTRY(sceRtc_driver),
	NID_ENTRY(sceImpose_driver),
	NID_ENTRY(sceSysreg_driver),
	NID_ENTRY(sceSyscon_driver),
	NID_ENTRY(sceClockgen_driver),
	NID_ENTRY(sceGe_driver),
	NID_ENTRY(sceDisplay_driver),
	NID_ENTRY(sceHprm_driver),
	NID_ENTRY(sceDve_driver),
	NID_ENTRY(sceCodec_driver),
	NID_ENTRY(sceCtrl_driver),
	NID_ENTRY(scePadSvc_driver),
};

u32 nid_fix_660_to_620_size = NELEMS(nid_fix_660_to_620);
