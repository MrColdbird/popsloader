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
	{ 0x02AEA33F, 0x310802A9, },
	{ 0x864EBFD7, 0x07C586A1, },
	{ 0xA4AC3934, 0xFDC97D28, },
	{ 0xB9796F69, 0xB4F00CB5, },
	{ 0xF5780DAA, 0x9F205D3E, },
	{ 0xFEB5C72B, 0xF12A62F7, },
};

static nid_entry ModuleMgrForKernel_nid[] = {
	{ 0xDF8FFFAB, 0x3FF74DF1, },
	{ 0xE3CCC6EA, 0x939E4270, },
};

static nid_entry LoadExecForKernel_nid[] = {
	{ 0x29413885, 0xC3474C2A, },
};

static nid_entry sceRtc_driver_nid[] = {
	{ 0x2F20DAF0, 0x4E267E02, },
	{ 0x43F38ED8, 0xE7B3ABF4, },
};

static nid_entry sceImpose_driver_nid[] = {
	{ 0x25011AAB, 0x28B97035, },
	{ 0x4D849B71, 0x5557F4E2, },
	{ 0x5314204F, 0x133DB99A, },
	{ 0x55864BD7, 0x0F067E16, },
	{ 0x8F1AC24D, 0xB497314D, },
	{ 0xC94AC8E2, 0xDC3BECFF, },
};

static nid_entry sceSysreg_driver_nid[] = {
	{ 0x119647A7, 0x0AE8E549, },
	{ 0x2B3BE2C8, 0x38527743, },
	{ 0x2D858336, 0x48F1C4AD, },
	{ 0x314A489C, 0xDB97C70E, },
	{ 0x4643F826, 0x0143E8A8, },
	{ 0x47966D28, 0x41B0337B, },
	{ 0x5D3DD0B3, 0x4634C9DC, },
	{ 0x94914740, 0x4B4CCE80, },
	{ 0x97EA6913, 0x457FEBA9, },
	{ 0x9EBB3C43, 0xC36775AD, },
	{ 0xB733A263, 0xB1751B06, },
	{ 0xE7849809, 0x8B1DD83A, },
};

static nid_entry sceSyscon_driver_nid[] = {
	{ 0xB757C11D, 0x48448373, },
	{ 0xF7E9487A, 0x9BC5E33B, },
};

static nid_entry sceClockgen_driver_nid[] = {
	{ 0xACC30ECE, 0xDAB6E612, },
};

static nid_entry sceGe_driver_nid[] = {
	{ 0x23E9F5FA, 0x4B9554EB, },
	{ 0x7E2381D2, 0xAFE6C9EF, },
	{ 0xD4D665C9, 0xD8633888, },
	{ 0xF489E74B, 0x5D28A52B, },
};

static nid_entry sceDisplay_driver_nid[] = {
	{ 0x0F82D90A, 0xE38CA615, },
	{ 0xAAC50D73, 0x03F16FD4, },
	{ 0xF4B7B531, 0xE97E9718, },
};

static nid_entry sceHprm_driver_nid[] = {
	{ 0x62CDFB12, 0xB2BEADB8, },
};

static nid_entry sceDve_driver_nid[] = {
	{ 0xA1401BA2, 0x48005974, },
};

static nid_entry sceCodec_driver_nid[] = {
	{ 0x794EE731, 0x376399B6, },
};

static nid_entry sceCtrl_driver_nid[] = {
	{ 0x7A6436DE, 0x6C86AF22, },
};

static nid_entry scePadSvc_driver_nid[] = {
	{ 0x1971BAE0, 0x7CAB5A3D, },
	{ 0x3B0567D6, 0x0B3E6FD3, },
	{ 0x79B60777, 0x05C9C803, },
};

static nid_entry InitForKernel_nid[] = {
	{ 0x977A0F90, 0x9D33A110, },
};

resolver_config nid_fix_620_to_660[] = {
	NID_ENTRY(SysMemForKernel),
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
	NID_ENTRY(InitForKernel),
};

u32 nid_fix_620_to_660_size = NELEMS(nid_fix_620_to_660);
