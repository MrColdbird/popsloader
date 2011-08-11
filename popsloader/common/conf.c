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

typedef struct _CONFIG {
	char disc_id[12];
	u32 version;
} CONFIG;

struct popsloader_config g_conf;

static char disc_id[16];
static int config_offset = -1;

static int get_disc_id()
{
	void* (*sceKernelGetGameInfo_k)();

	memset(disc_id, 0, sizeof(disc_id));
	sceKernelGetGameInfo_k = (void *)sctrlHENFindFunction("sceSystemMemoryManager", "SysMemForKernel", 0xCD617A94); 

	if(sceKernelGetGameInfo_k != NULL) {
		char *info_buff = sceKernelGetGameInfo_k();
		memcpy(disc_id, info_buff + 0x44, 9);
	}

	return 0;
}

int save_config(void)
{
	SceUID fd;
	char path[256];
	CONFIG cnf;

	sprintf(path, "%s%s", is_ef0() ? "ef" : "ms", CFG_PATH);
	fd = sceIoOpen(path, (config_offset >= 0)? PSP_O_RDWR : PSP_O_WRONLY | PSP_O_CREAT | PSP_O_APPEND, 0777);

	if(fd < 0) {
		return fd;
	}

	memset(&cnf, 0, sizeof(cnf));
	memcpy(cnf.disc_id, disc_id, 12);
	cnf.version = g_conf.pops_fw_version;

	if(config_offset >= 0) {
		sceIoLseek(fd, config_offset * sizeof(CONFIG), PSP_SEEK_SET);
	}

	sceIoWrite(fd, &cnf, sizeof(cnf));
	sceIoClose(fd);

	return 0;
}

static int _load_config(void)
{
	SceUID fd;
	char path[256];
	CONFIG config[32];
	int size;
	int offset = 0;

	sprintf(path, "%s%s", is_ef0() ? "ef" : "ms", CFG_PATH);
	fd = sceIoOpen(path, PSP_O_RDONLY, 0777);

	if(fd < 0) {
		return fd;
	}

	while((size = sceIoRead(fd, config, sizeof(CONFIG) * 32))  > 0) {
		int cnt = size / sizeof(CONFIG);		

		if(cnt > 0) {
			int i;

			for(i=0; i<cnt; i++) {
				if(0 == memcmp(disc_id, config[i].disc_id, 9)) {		
					sceIoClose(fd);
					g_conf.pops_fw_version = config[i].version;
					config_offset = offset + i;

					return 0;
				}	
			}

			offset += cnt;
		}
	}

	sceIoClose(fd);

	return -1;
}

int load_config(void)
{
	int ret;

	get_disc_id();
	ret = _load_config();

	if(ret < 0) {
		def_config(&g_conf);
		save_config();
	}

	return 0;
}

void def_config(struct popsloader_config *conf)
{
	conf->pops_fw_version = 0;
}
