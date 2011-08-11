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
	{ 0x07C586A1, 0x864EBFD7, },
	{ 0x310802A9, 0x02AEA33F, },
	{ 0x8AE776AF, 0x74F3DC82, },
	{ 0xB4F00CB5, 0xB9796F69, },
	{ 0xC90B0992, 0xF5780DAA, },
	{ 0xF12A62F7, 0xFEB5C72B, },
	{ 0xFDC97D28, 0xA4AC3934, },
};

static nid_entry InitForKernel_nid[] = {
	{ 0x9D33A110, 0x977A0F90, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0x3FF74DF1, 0xDF8FFFAB, },
	{ 0x939E4270, 0xE3CCC6EA, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0xC3474C2A, 0x29413885, },
};

static nid_entry sceRtc_driver_nid[] = {
	{ 0x4E267E02, 0x2F20DAF0, },
	{ 0xE7B3ABF4, 0x7ED29E40, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x0F067E16, 0x55864BD7, },
	{ 0x133DB99A, 0x5314204F, },
	{ 0x28B97035, 0x25011AAB, },
	{ 0x5557F4E2, 0x4D849B71, },
	{ 0xB497314D, 0x8F1AC24D, },
	{ 0xDC3BECFF, 0xC94AC8E2, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x0AE8E549, 0x119647A7, },
	{ 0x38527743, 0x2B3BE2C8, },
	{ 0x41B0337B, 0x47966D28, },
	{ 0x457FEBA9, 0x97EA6913, },
	{ 0x4634C9DC, 0x5D3DD0B3, },
	{ 0x48F1C4AD, 0x2D858336, },
	{ 0x4B4CCE80, 0x94914740, },
	{ 0x8B1DD83A, 0xE7849809, },
	{ 0xB1751B06, 0xB733A263, },
	{ 0xC36775AD, 0x9EBB3C43, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0x48448373, 0xB757C11D, },
	{ 0x9BC5E33B, 0xF7E9487A, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xDAB6E612, 0xACC30ECE, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x4B9554EB, 0x23E9F5FA, },
	{ 0x5D28A52B, 0xF489E74B, },
	{ 0xAFE6C9EF, 0x7E2381D2, },
	{ 0xD8633888, 0xD4D665C9, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x03F16FD4, 0xAAC50D73, },
	{ 0xE38CA615, 0x0F82D90A, },
	{ 0xE97E9718, 0xF4B7B531, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0xB2BEADB8, 0x62CDFB12, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0x48005974, 0xA1401BA2, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0x376399B6, 0x794EE731, },
};

static nid_entry sceCtrl_driver_nid[] = {
	{ 0x6C86AF22, 0x7A6436DE, },
};

static nid_entry scePadSvc_driver_nid[] = {
	{ 0x05C9C803, 0x79B60777, },
	{ 0x0B3E6FD3, 0x3B0567D6, },
	{ 0x7CAB5A3D, 0x1971BAE0, },
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
