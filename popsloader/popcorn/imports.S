	.set noreorder

#include "pspstub.s"

	STUB_START "SysMemForKernel",0x40000011,0x00020005
	STUB_FUNC  0x419DB8F4,sceKernelRegisterGetIdFunc
	STUB_FUNC  0x6373995D,sceKernelGetModel
	STUB_END
