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
	{ 0x07C586A1, 0x458A70B5, },
	{ 0x310802A9, 0x25A760F0, },
	{ 0x8AE776AF, 0x2CFE3B22, },
	{ 0xB4F00CB5, 0xF0E0AB7A, },
	{ 0xC90B0992, 0x3DE3C6DF, },
	{ 0xF12A62F7, 0x52B54B93, },
	{ 0xFDC97D28, 0xF2FEAFD5, },
};

static nid_entry InitForKernel_nid[] = {
	{ 0x9D33A110, 0xEE67E450, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x3FF74DF1, 0xE6BF3960, },
	{ 0x939E4270, 0xFFB9B760, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xC3474C2A, 0xFCD765C9, },
};

static nid_entry sceRtc_driver_nid[] = {
	{ 0x4E267E02, 0xFF530D9F, },
	{ 0xE7B3ABF4, 0x99037763, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x0F067E16, 0x44F17A7A, },
	{ 0x133DB99A, 0x3BD9E51B, },
	{ 0x28B97035, 0x027F21C6, },
	{ 0x5557F4E2, 0xEBC850AC, },
	{ 0xB497314D, 0x3FE74F52, },
	{ 0xDC3BECFF, 0x4C4DF719, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x0AE8E549, 0x86FFE348, },
	{ 0x38527743, 0xD74D9041, },
	{ 0x41B0337B, 0x9E80B4E2, },
	{ 0x457FEBA9, 0xB70793D7, },
	{ 0x4634C9DC, 0xD1999F94, },
	{ 0x48F1C4AD, 0xE2606FCB, },
	{ 0x4B4CCE80, 0x9984A972, },
	{ 0x8B1DD83A, 0x789597AB, },
	{ 0xB1751B06, 0x8E9E76AE, },
	{ 0xC36775AD, 0x3A98CABB, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x48448373, 0x741110C5, },
	{ 0x9BC5E33B, 0xC4931159, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xDAB6E612, 0xA02BB1D3, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x4B9554EB, 0xFEEC36F7, },
	{ 0x5D28A52B, 0x670F15ED, },
	{ 0xAFE6C9EF, 0xD8A53104, },
	{ 0xD8633888, 0x2444EC4D, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x03F16FD4, 0x3DABE438, },
	{ 0xE38CA615, 0x3E4B1B28, },
	{ 0xE97E9718, 0x8930B3A9, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0xB2BEADB8, 0xADE4B1F4, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x48005974, 0xAA085C2A, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0x376399B6, 0xB2EF6B19, },
};

static nid_entry sceCtrl_driver_nid[] = {
	{ 0x6C86AF22, 0xDEFAD580, },
};

static nid_entry scePadSvc_driver_nid[] = {
	{ 0x05C9C803, 0x773BA62B, },
	{ 0x0B3E6FD3, 0x2F9A534A, },
	{ 0x7CAB5A3D, 0x830FC570, },
};

resolver_config nid_fix_660_to_635[] = {
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

u32 nid_fix_660_to_635_size = NELEMS(nid_fix_660_to_635);
