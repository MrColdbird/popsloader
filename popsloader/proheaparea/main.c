#include <pspsdk.h>
#include <pspsysmem.h>

PSP_MODULE_INFO("PROPafHeaparea_Module", 0x0000, 1, 0);

SceUID g_fpl = -1, g_fpl2 = -1;
void *g_fpl_address = NULL, *g_fpl_address2 = NULL;

extern int sceKernelQueryMemoryInfo(int *addr, int *memid, int unk);

u32 system_heap_size = 0x00230000;
u32 paf_heap_size = 0x00030000;

void scePafHeaparea_F50AAE41(void **address, u32 *size)
{
	*address = g_fpl_address;
	*size = system_heap_size;
}

void scePafHeaparea_ACCE25B2(void **address, u32 *size)
{
	*address = g_fpl_address2;
	*size = paf_heap_size;
}

int module_start(SceSize args, void* argp)
{
	int memid = 0, ret;
	int unk = 0x05000001;
	
	ret = sceKernelQueryMemoryInfo(&unk, &memid, 0);

	if(ret < 0) {
		return ret;
	}

	g_fpl = sceKernelCreateFpl("ScePafSystemHeaparea", memid, 0, system_heap_size, 1, NULL);

	if(g_fpl < 0) {
		return g_fpl;
	}

	sceKernelTryAllocateFpl(g_fpl, &g_fpl_address);

	g_fpl2 = sceKernelCreateFpl("ScePafLonglifeHeaparea", memid, 0, paf_heap_size, 1, NULL);

	if(g_fpl2 < 0) {
		return g_fpl2;
	}
	
	sceKernelTryAllocateFpl(g_fpl2, &g_fpl_address2);

	return 0;
}

int module_stop(SceSize args, void* argp)
{
	sceKernelFreeFpl(g_fpl, g_fpl_address);
	sceKernelDeleteFpl(g_fpl);
	sceKernelFreeFpl(g_fpl2, g_fpl_address2);
	sceKernelDeleteFpl(g_fpl2);

	return 0;
}
