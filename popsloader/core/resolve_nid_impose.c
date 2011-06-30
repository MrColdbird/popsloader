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

resolver_config *nid_impose_fix = NULL;
u32 nid_impose_fix_size = 0;

void setup_nid_resolver_impose(void)
{
	if(psp_fw_version == FW_620) {
		nid_impose_fix_size = nid_impose_fix_400_to_620_size;
		nid_impose_fix = nid_impose_fix_400_to_620;
	}

	if(psp_fw_version == FW_635 || psp_fw_version == FW_639) {
		nid_impose_fix_size = nid_impose_fix_400_to_635_size;
		nid_impose_fix = nid_impose_fix_400_to_635;
	}
}

resolver_config* get_nid_resolver_impose(const char *libname)
{
	int i;

	for(i=0; i<nid_impose_fix_size; ++i) {
		if (!strcmp(libname, nid_impose_fix[i].name)) {
			return &nid_impose_fix[i];
		}
	}

	return NULL;
}

u32 resolve_nid_impose(resolver_config *resolver, u32 nid)
{
	int i;
	u32 new;

	for(i=0; i<resolver->nidcount; ++i) {
		new = resolver->nidtable[i].new;

		if(new != UNKNOWNNID && nid == resolver->nidtable[i].old) {
//			printk("%s: %s_%08X->%s_%08X\n", __func__, resolver->name, nid, resolver->name, new);

			return new;
		}
	}

	return nid;
}

void fix_nid_impose(SceModule *mod_)
{
	SceModule2 *mod = (SceModule2*)mod_;
	int offset, i;
	u32 stubcount;
	struct SceLibraryStubTable *stub;
	resolver_config *resolver;
	int size;
	char *buf;

	if(nid_impose_fix == NULL) {
		return;
	}

	offset = 0;
	buf = mod->stub_top;
	size = mod->stub_size;

	while(offset < size) {
		stub = (struct SceLibraryStubTable *)(buf + offset);
		stubcount = stub->stubcount;
		resolver = get_nid_resolver_impose(stub->libname);

		if(resolver != NULL) {
			for (i=0; i<stubcount; i++) {
				u32 newnid;

				newnid = resolve_nid_impose(resolver, stub->nidtable[i]);

				if(newnid != stub->nidtable[i]) {
					stub->nidtable[i] = newnid;
				}
			}
		}

		offset += stub->len << 2;
	}
}
