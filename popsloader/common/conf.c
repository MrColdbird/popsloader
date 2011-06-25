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
#include <pspsysmem_kernel.h>
#include <pspthreadman_kernel.h>
#include <pspctrl.h>
#include <pspiofilemgr_kernel.h>
#include <psprtc.h>
#include "popsloader.h"
#include "utils.h"
#include "libs.h"
#include "strsafe.h"
#include "systemctrl.h"
#include "main.h"

struct popsloader_config g_conf;

static inline int is_ef0(void)
{
	return psp_model == PSP_GO && sctrlKernelBootFrom() == 0x50 ? 1 : 0;
}

int save_config(void)
{
	SceUID fd;
	char path[256];

	sprintf(path, "%s%s", is_ef0() ? "ef" : "ms", CFG_PATH);
	fd = sceIoOpen(path, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);

	if(fd < 0) {
		return fd;
	}

	sceIoWrite(fd, &g_conf, sizeof(g_conf));
	sceIoClose(fd);

	return 0;
}

static int _load_config(void)
{
	SceUID fd;
	char path[256];

	sprintf(path, "%s%s", is_ef0() ? "ef" : "ms", CFG_PATH);
	fd = sceIoOpen(path, PSP_O_RDONLY, 0777);

	if(fd < 0) {
		return fd;
	}

	sceIoRead(fd, &g_conf, sizeof(g_conf));
	sceIoClose(fd);

	return 0;
}

int load_config(void)
{
	int ret;

	ret = _load_config();

	if(ret < 0) {
		def_config(&g_conf);
	}

	return 0;
}

void def_config(struct popsloader_config *conf)
{
	conf->pops_fw_version = psp_fw_version;
}
