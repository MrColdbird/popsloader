	.set noreorder

#include "pspstub.s"

	STUB_START "SysMemUserForUser",0x40000011,0x00010005
	STUB_FUNC  0x2A3E5280,sceKernelQueryMemoryInfo
	STUB_END
