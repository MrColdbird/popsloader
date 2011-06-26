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
#include <psputilsforkernel.h>
#include <pspsysevent.h>
#include <pspiofilemgr.h>
#include <stdio.h>
#include <string.h>
#include "systemctrl.h"
#include "utils.h"
#include "main.h"

void sync_cache(void)
{
	sceKernelIcacheInvalidateAll();
	sceKernelDcacheWritebackInvalidateAll();
}

#ifdef DEBUG
char ownisgraph (u8 c)
{
    if ( c >= 0x21 && c <= 0x7e )
        return 1;

    return 0;
}

void hexdump(void *addr, int size)
{
	int i;
	u8 *p = (u8*)addr;

	if (addr == NULL) {
		printk("hexdump: <NULL>\n");

		return;
	}

	if (size == 0) {
		printk("hexdump: size 0\n");
		
		return;
	}

	printk("Address:   ");
	i=0; for(;i<16; ++i) {
		if (i == 8)
			printk("- ");
		
		printk("%02X ", i);
	}

	i=0; for(;i<16; ++i) {
		printk("%1X", i);
	}

	printk("\n-----------------------------------------------------------------------------\n");

	i=0;
	printk("0x%08X ", i);
	
	for(; i<size; ++i) {
		if (i != 0 && i % 16 == 0) {
			int j;

			for(j=16; j>0; --j) {
				if(ownisgraph(p[i-j])) {
					printk("%c", p[i-j]);
				} else {
					printk(".");
				}
			}
			printk("\n0x%08X ", i);
		}

		if (i != 0 && i % 8 == 0 && i % 16 != 0) {
			printk("- ");
		}

		printk("%02X ", p[i]);
	}

	int rest = (16-(i%16));

	rest = rest == 16 ? 0 : rest;
	int j; for(j=0; j<rest; j++) {
		if (j+(i%16) == 8)
			printk("  ");
		printk("   ");
	}

	rest = i % 16;
	rest = rest == 0 ? 16 : rest;

	for(j=rest; j>0; --j) {
		if(ownisgraph(p[i-j])) {
			printk("%c", p[i-j]);
		} else {
			printk(".");
		}
	}

	printk("\n");
}

void fill_vram(u32 color)
{
	u32 *p = (u32*)0x44000000;

	while (p < (u32*)0x44200000)
		*p++ = color;
}
#endif
