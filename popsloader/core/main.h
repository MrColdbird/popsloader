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

#ifndef MAIN_H
#define MAIN_H

#define USE_PRINTK 1
//#undef USE_PRINTK

#ifdef USE_PRINTK
#include "printk.h"
#else
#ifdef DEBUG
#define printk pspDebugScreenPrintf

static inline void printk_init()
{
	pspDebugScreenInit();
}

#else
#define printk(...)
#define printk_init(...)
#endif
#endif

#define UNKNOWNNID 0xDEADBEEF
#define NID_ENTRY(libname) \
	{ #libname, NELEMS(libname##_nid), libname##_nid, }

typedef struct _nid_entry {
	u32 old;
	u32 new;
} nid_entry;

typedef struct _resolver_config {
	char *name;
	u32 nidcount;
	nid_entry *nidtable;
} resolver_config;

extern resolver_config nid_fix_660_to_620[];
extern u32 nid_fix_660_to_620_size;
extern resolver_config nid_fix_660_to_635[];
extern u32 nid_fix_660_to_635_size;
extern resolver_config nid_fix_635_to_620[];
extern u32 nid_fix_635_to_620_size;
extern resolver_config nid_fix_635_to_660[];
extern u32 nid_fix_635_to_660_size;
extern resolver_config nid_fix_620_to_635[];
extern u32 nid_fix_620_to_635_size;
extern resolver_config nid_fix_620_to_660[];
extern u32 nid_fix_620_to_660_size;
extern resolver_config nid_fix_500_to_635[];
extern u32 nid_fix_500_to_635_size;
extern resolver_config nid_fix_500_to_620[];
extern u32 nid_fix_500_to_620_size;
extern resolver_config nid_fix_500_to_660[];
extern u32 nid_fix_500_to_660_size;
extern resolver_config nid_fix_400_to_620[];
extern u32 nid_fix_400_to_620_size;
extern resolver_config nid_fix_400_to_635[];
extern u32 nid_fix_400_to_635_size;
extern resolver_config nid_fix_400_to_660[];
extern u32 nid_fix_400_to_660_size;
extern resolver_config nid_fix_373_to_620[];
extern u32 nid_fix_373_to_620_size;
extern resolver_config nid_fix_373_to_635[];
extern u32 nid_fix_373_to_635_size;
extern resolver_config nid_fix_373_to_660[];
extern u32 nid_fix_373_to_660_size;
extern resolver_config nid_fix_393_to_620[];
extern u32 nid_fix_393_to_620_size;
extern resolver_config nid_fix_393_to_635[];
extern u32 nid_fix_393_to_635_size;
extern resolver_config nid_fix_393_to_660[];
extern u32 nid_fix_393_to_660_size;
extern resolver_config nid_impose_fix_400_to_620[];
extern u32 nid_impose_fix_400_to_620_size;
extern resolver_config nid_impose_fix_400_to_635[];
extern u32 nid_impose_fix_400_to_635_size;
extern resolver_config nid_impose_fix_400_to_660[];
extern u32 nid_impose_fix_400_to_660_size;

void fix_nid(SceModule* mod);
void fix_nid_impose(SceModule* mod);
void setup_nid_resolver(void);
void setup_nid_resolver_impose(void);

extern u32 psp_fw_version;
extern u32 psp_model;
extern u32 pops_fw_version;

void patch_sceImposeGetParam(void);
int custom_start_module(int modid, SceSize argsize, void *argp, int *modstatus, SceKernelSMOption *opt);
int is_ef0(void);
const char *get_module_prefix(void);
void mount_memory_stick(void);

#endif
