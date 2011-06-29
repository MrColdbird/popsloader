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

#include <pspsdk.h>
#include "popcorn_patch_offset.h"

#if !defined(CONFIG_635) && !defined(CONFIG_620) && !defined(CONFIG_639) && !defined(CONFIG_610) && !defined(CONFIG_600) && !defined(CONFIG_551) && !defined(CONFIG_550) && !defined(CONFIG_503) && !defined(CONFIG_501) && !defined(CONFIG_500) && !defined(CONFIG_400) && !defined(CONFIG_373) && !defined(CONFIG_371) && !defined(CONFIG_352) && !defined(CONFIG_351) && !defined(CONFIG_350) && !defined(CONFIG_340) && !defined(CONFIG_330) && !defined(CONFIG_311) && !defined(CONFIG_310)  && !defined(CONFIG_303) && !defined(CONFIG_302)
#error You have to define one of CONFIG_FW_VERSION
#endif

#ifdef CONFIG_639
PatchOffset g_639_offsets = {
	.fw_version = FW_639,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x00002798,
		.get_rif_path_call2 = 0x00002C58,
		.sceNpDrmGetVersionKeyCall = 0x000029C4,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002DA8,
		.scePopsManLoadModuleCheck = 0x00001E80,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000D5654, 0x0000DC04 }, // 01G
			{ 0x000D671C, 0x0000DC04 }, // 02G
			{ 0x000D671C, 0x0000DC04 }, // 03G
			{ 0x000D670C, 0x0000DC04 }, // 04G
			{ 0x000D8698, 0x0000E31C }, // 05G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D670C, 0x0000DC04 }, // 07G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D670C, 0x0000DC04 }, // 09G
		},
		.ICON0SizeOffset = {
			0x00036F54, // 01G
			0x00037F90, // 02G
			0x00037F90, // 03G
			0x00037F90, // 04G
			0x00039D78, // 05G
			0xDEADBEEF, // unused
			0x00037F90, // 07G
			0xDEADBEEF, // unused
			0x00037F90, // 09G
		},
		.manualNameCheck = {
			0x0002541C, // 01G
			0x00025928, // 02G
			0x00025928, // 03G
			0x00025928, // 04G
			0x000261BC, // 05G
			0xDEADBEEF, // unused
			0x00025928, // 07G
			0xDEADBEEF, // unused
			0x00025928, // 09G
		},
		.sceMeAudio_67CD7972_NID = 0x67CD7972,
	},
};
#endif

#ifdef CONFIG_635
PatchOffset g_635_offsets = {
	.fw_version = FW_635,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x00002798,
		.get_rif_path_call2 = 0x00002C58,
		.sceNpDrmGetVersionKeyCall = 0x000029C4,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002DA8,
		.scePopsManLoadModuleCheck = 0x00001E80,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000D5404, 0x0000DAC0 }, // 01G
			{ 0x000D64BC, 0x0000DAC0 }, // 02G
			{ 0x000D64BC, 0x0000DAC0 }, // 03G
			{ 0x000D64FC, 0x0000DB00 }, // 04G
			{ 0x000D8488, 0x0000E218 }, // 05G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D64FC, 0x0000DB00 }, // 07G
			{ 0x00000000, 0x00000000 }, // unused
			{ 0x000D64FC, 0x0000DB00 }, // 09G
		},
		.ICON0SizeOffset = {
			0x00036CF8, // 01G
			0x00037D34, // 02G
			0x00037D34, // 03G
			0x00037D74, // 04G
			0x00039B5C, // 05G
			0xDEADBEEF, // unused
			0x00037D74, // 07G
			0xDEADBEEF, // unused
			0x00037D74, // 09G
		},
		.manualNameCheck = {
			0x000251C0, // 01G
			0x000256CC, // 02G
			0x000256CC, // 03G
			0x0002570C, // 04G
			0x00025FA0, // 05G
			0xDEADBEEF, // unused
			0x0002570C, // 07G
			0xDEADBEEF, // unused
			0x0002570C, // 09G
		},
		.sceMeAudio_67CD7972_NID = 0x67CD7972,
	},
};
#endif

#ifdef CONFIG_620
PatchOffset g_620_offsets = {
	.fw_version = FW_620,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x00002824,
		.get_rif_path_call2 = 0x00002CE4,
		.sceNpDrmGetVersionKeyCall = 0x00002A50,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002E34,
		.scePopsManLoadModuleCheck = 0x00001EA8,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000DA600, 0x0000DE18 }, // 01G
			{ 0x000DA600, 0x0000DE18 }, // 02G
			{ 0x000DA600, 0x0000DE18 }, // 03G
			{ 0x000DA630, 0x0000DE1C }, // 04G
			{ 0x000DC5CC, 0x0000E534 }, // 05G
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0x000DA630, 0x0000DE1C }, // unused
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0x000DA630, 0x0000DE1C }, // unused
		},
		.ICON0SizeOffset = {
			0x0003BCD0, // 01G
			0x0003BCD0, // 02G
			0x0003BCD0, // 03G
			0x0003BCFC, // 04G
			0x0003DAE4, // 05G
			0xDEADBEEF, // unused
			0x0003BCFC, // unused
			0xDEADBEEF, // unused
			0x0003BCFC, // unused
		},
		.manualNameCheck = {
			0x00029710, // 01G
			0x00029710, // 02G
			0x00029710, // 03G
			0x0002973C, // 04G
			0x00029FD0, // 05G
			0xDEADBEEF, // unused
			0x0002973C, // unused
			0xDEADBEEF, // unused
			0x0002973C, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xF43E573A,
	},
};
#endif

#ifdef CONFIG_610
PatchOffset g_610_offsets = {
	.fw_version = FW_610,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x0000239C,
		.get_rif_path_call2 = 0x0000291C,
		.sceNpDrmGetVersionKeyCall = 0x000025C8,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002A88,
		.scePopsManLoadModuleCheck = 0x00001A48,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000CC83C, 0x0000D6B8 }, // 01G
			{ 0x000CC83C, 0x0000D6B8 }, // 02G
			{ 0x000CC83C, 0x0000D6B8 }, // 03G
			{ 0x000CC88C, 0x0000D6FC }, // 04G
			{ 0x000CE4E8, 0x0000DE08 }, // 05G
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0x000CC88C, 0x0000D6FC }, // unused
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0x000CC88C, 0x0000D6FC }, // unused
		},
		.ICON0SizeOffset = {
			0x0002E454, // 01G
			0x0002E454, // 02G
			0x0002E454, // 03G
			0x0002E49C, // 04G
			0x0002FF50, // 05G
			0xDEADBEEF, // unused
			0x0002E49C, // unused
			0xDEADBEEF, // unused
			0x0002E49C, // unused
		},
		.manualNameCheck = {
			0x0001C418, // 01G
			0x0001C418, // 02G
			0x0001C418, // 03G
			0x0001C460, // 04G
			0x0001CCC4, // 05G
			0xDEADBEEF, // unused
			0x0001C460, // unused
			0xDEADBEEF, // unused
			0x0001C460, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xF43E573A,
	},
};
#endif

#ifdef CONFIG_600
PatchOffset g_600_offsets = {
	.fw_version = FW_600,
	.popsman_patch = {
		.get_rif_path = 0x00000190,
		.get_rif_path_call1 = 0x0000239C,
		.get_rif_path_call2 = 0x0000291C,
		.sceNpDrmGetVersionKeyCall = 0x000025C8,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00002A88,
		.scePopsManLoadModuleCheck = 0x00001A48,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000CC82C, 0x0000D6B8 }, // 01G
			{ 0x000CC82C, 0x0000D6B8 }, // 02G
			{ 0x000CC82C, 0x0000D6B8 }, // 03G
			{ 0x000CC87C, 0x0000D6FC }, // 04G
			{ 0xDEADBEEF, 0xDEADBEEF }, // 05G TODO
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0x000CC87C, 0x000CC87C }, // unused
			{ 0xDEADBEEF, 0xDEADBEEF }, // unused
			{ 0x000CC87C, 0x000CC87C }, // unused
		},
		.ICON0SizeOffset = {
			0x0002E440, // 01G
			0x0002E440, // 02G
			0x0002E440, // 03G
			0x0002E488, // 04G
			0xDEADBEEF, // 05G TODO
			0xDEADBEEF, // unused
			0x0002E488, // unused
			0xDEADBEEF, // unused
			0x0002E488, // unused
		},
		.manualNameCheck = {
			0x0001C404, // 01G
			0x0001C404, // 02G
			0x0001C404, // 03G
			0x0001C44C, // 04G
			0xDEADBEEF, // 05G TODO
			0xDEADBEEF, // unused
			0x0001C44C, // unused
			0xDEADBEEF, // unused
			0x0001C44C, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xF43E573A,
	},
};
#endif

#ifdef CONFIG_551
PatchOffset g_551_offsets = {
	.fw_version = FW_551,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00000144,
		.scePopsManLoadModuleCheck = 0x000015C0,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000CEDB8, 0x0000E84C }, // 01G
			{ 0x000CEDB8, 0x0000E84C }, // 02G
			{ 0x000CEDB8, 0x0000E84C }, // 03G
			{ 0x000CEDB8, 0x0000E84C }, // 04G
			{ 0x000CEDB8, 0x0000E84C }, // 05G
			{ 0x000CEDB8, 0x0000E84C }, // unused
			{ 0x000CEDB8, 0x0000E84C }, // unused
			{ 0x000CEDB8, 0x0000E84C }, // unused
			{ 0x000CEDB8, 0x0000E84C }, // unused
		},
		.ICON0SizeOffset = {
			0x00030778, // 01G
			0x00030778, // 02G
			0x00030778, // 03G
			0x00030778, // 04G
			0x00030778, // 05G
			0x00030778, // unused
			0x00030778, // unused
			0x00030778, // unused
			0x00030778, // unused
		},
		.manualNameCheck = {
			0x0001FBD4, // 01G
			0x0001FBD4, // 02G
			0x0001FBD4, // 03G
			0x0001FBD4, // 04G
			0x0001FBD4, // 05G
			0x0001FBD4, // unused
			0x0001FBD4, // unused
			0x0001FBD4, // unused
			0x0001FBD4, // unused
		},
		.sceMeAudio_67CD7972_NID = 0x1BDF9405,
	},
};
#endif

#ifdef CONFIG_550
PatchOffset g_550_offsets = {
	.fw_version = FW_550,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00000144,
		.scePopsManLoadModuleCheck = 0x0000158C,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000CEDB8, 0x0000E834 }, // 01G
			{ 0x000CEDB8, 0x0000E834 }, // 02G
			{ 0x000CEDB8, 0x0000E834 }, // 03G
			{ 0x000CEDB8, 0x0000E834 }, // 04G
			{ 0x000CEDB8, 0x0000E834 }, // 05G
			{ 0x000CEDB8, 0x0000E834 }, // unused
			{ 0x000CEDB8, 0x0000E834 }, // unused
			{ 0x000CEDB8, 0x0000E834 }, // unused
			{ 0x000CEDB8, 0x0000E834 }, // unused
		},
		.ICON0SizeOffset = {
			0x00030704, // 01G
			0x00030704, // 02G
			0x00030704, // 03G
			0x00030704, // 04G
			0x00030704, // 05G
			0x00030704, // unused
			0x00030704, // unused
			0x00030704, // unused
			0x00030704, // unused
		},
		.manualNameCheck = {
			0x0001FB60, // 01G
			0x0001FB60, // 02G
			0x0001FB60, // 03G
			0x0001FB60, // 04G
			0x0001FB60, // 05G
			0x0001FB60, // unused
			0x0001FB60, // unused
			0x0001FB60, // unused
			0x0001FB60, // unused
		},
		.sceMeAudio_67CD7972_NID = 0x1BDF9405,
	},
};
#endif

#ifdef CONFIG_503
PatchOffset g_503_offsets = {
	.fw_version = FW_503,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00000144,
		.scePopsManLoadModuleCheck = 0x0000158C,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000C588C, 0x0000E958 }, // 01G
			{ 0x000C588C, 0x0000E958 }, // 02G
			{ 0x000C588C, 0x0000E958 }, // 03G
			{ 0x000C588C, 0x0000E958 }, // 04G
			{ 0x000C588C, 0x0000E958 }, // 05G
			{ 0x000C588C, 0x0000E958 }, // unused
			{ 0x000C588C, 0x0000E958 }, // unused
			{ 0x000C588C, 0x0000E958 }, // unused
			{ 0x000C588C, 0x0000E958 }, // unused
		},
		.ICON0SizeOffset = {
			0x000273A8, // 01G
			0x000273A8, // 02G
			0x000273A8, // 03G
			0x000273A8, // 04G
			0x000273A8, // 05G
			0x000273A8, // unused
			0x000273A8, // unused
			0x000273A8, // unused
			0x000273A8, // unused
		},
		.manualNameCheck = {
			0x000190F8, // 01G
			0x000190F8, // 02G
			0x000190F8, // 03G
			0x000190F8, // 04G
			0x000190F8, // 05G
			0x000190F8, // unused
			0x000190F8, // unused
			0x000190F8, // unused
			0x000190F8, // unused
		},
		.sceMeAudio_67CD7972_NID = 0x1BDF9405,
	},
};
#endif

#ifdef CONFIG_501
PatchOffset g_501_offsets = {
	.fw_version = FW_501,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00000144,
		.scePopsManLoadModuleCheck = 0x0000158C,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000C583C, 0x0000E90C }, // 01G
			{ 0x000C583C, 0x0000E90C }, // 02G
			{ 0x000C583C, 0x0000E90C }, // 03G
			{ 0x000C583C, 0x0000E90C }, // 04G
			{ 0x000C583C, 0x0000E90C }, // 05G
			{ 0x000C583C, 0x0000E90C }, // unused
			{ 0x000C583C, 0x0000E90C }, // unused
			{ 0x000C583C, 0x0000E90C }, // unused
			{ 0x000C583C, 0x0000E90C }, // unused
		},
		.ICON0SizeOffset = {
			0x00027354, // 01G
			0x00027354, // 02G
			0x00027354, // 03G
			0x00027354, // 04G
			0x00027354, // 05G
			0x00027354, // unused
			0x00027354, // unused
			0x00027354, // unused
			0x00027354, // unused
		},
		.manualNameCheck = {
			0x000190A4, // 01G
			0x000190A4, // 02G
			0x000190A4, // 03G
			0x000190A4, // 04G
			0x000190A4, // 05G
			0x000190A4, // unused
			0x000190A4, // unused
			0x000190A4, // unused
			0x000190A4, // unused
		},
		.sceMeAudio_67CD7972_NID = 0x1BDF9405,
	},
};
#endif

#ifdef CONFIG_500
PatchOffset g_500_offsets = {
	.fw_version = FW_500,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00000144,
		.scePopsManLoadModuleCheck = 0x0000158C,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000C583C, 0x0000E90C }, // 01G
			{ 0x000C583C, 0x0000E90C }, // 02G
			{ 0x000C583C, 0x0000E90C }, // 03G
			{ 0x000C583C, 0x0000E90C }, // 04G
			{ 0x000C583C, 0x0000E90C }, // 05G
			{ 0x000C583C, 0x0000E90C }, // unused
			{ 0x000C583C, 0x0000E90C }, // unused
			{ 0x000C583C, 0x0000E90C }, // unused
			{ 0x000C583C, 0x0000E90C }, // unused
		},
		.ICON0SizeOffset = {
			0x0002734C, // 01G
			0x0002734C, // 02G
			0x0002734C, // 03G
			0x0002734C, // 04G
			0x0002734C, // 05G
			0x0002734C, // unused
			0x0002734C, // unused
			0x0002734C, // unused
			0x0002734C, // unused
		},
		.manualNameCheck = {
			0x0001909C, // 01G
			0x0001909C, // 02G
			0x0001909C, // 03G
			0x0001909C, // 04G
			0x0001909C, // 05G
			0x0001909C, // unused
			0x0001909C, // unused
			0x0001909C, // unused
			0x0001909C, // unused
		},
		.sceMeAudio_67CD7972_NID = 0x1BDF9405,
	},
};
#endif

#ifdef CONFIG_400
PatchOffset g_400_offsets = {
	.fw_version = FW_400,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00000138,
		.scePopsManLoadModuleCheck = 0x000015F0,
	},
	.pops_patch = {
		.decomp = {
			{ 0x000CC12C, 0x000119CC }, // 01G
			{ 0x000CC12C, 0x000119CC }, // 02G
			{ 0x000CC12C, 0x000119CC }, // 03G
			{ 0x000CC12C, 0x000119CC }, // 04G
			{ 0x000CC12C, 0x000119CC }, // 05G
			{ 0x000CC12C, 0x000119CC }, // unused
			{ 0x000CC12C, 0x000119CC }, // unused
			{ 0x000CC12C, 0x000119CC }, // unused
			{ 0x000CC12C, 0x000119CC }, // unused
		},
		.ICON0SizeOffset = {
			0x0002CF88, // 01G
			0x0002CF88, // 02G
			0x0002CF88, // 03G
			0x0002CF88, // 04G
			0x0002CF88, // 05G
			0x0002CF88, // unused
			0x0002CF88, // unused
			0x0002CF88, // unused
			0x0002CF88, // unused
		},
		.manualNameCheck = {
			0x0001C044, // 01G
			0x0001C044, // 02G
			0x0001C044, // 03G
			0x0001C044, // 04G
			0x0001C044, // 05G
			0x0001C044, // unused
			0x0001C044, // unused
			0x0001C044, // unused
			0x0001C044, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xBCC74871,
	},
};
#endif

#ifdef CONFIG_373
PatchOffset g_373_offsets = {
	.fw_version = FW_373,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x00000138,
		.scePopsManLoadModuleCheck = 0x000014B8,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0002D480, 0x00013D6C }, // 01G
			{ 0x0002D480, 0x00013D6C }, // 02G
			{ 0x0002D480, 0x00013D6C }, // 03G
			{ 0x0002D480, 0x00013D6C }, // 04G
			{ 0x0002D480, 0x00013D6C }, // 05G
			{ 0x0002D480, 0x00013D6C }, // unused
			{ 0x0002D480, 0x00013D6C }, // unused
			{ 0x0002D480, 0x00013D6C }, // unused
			{ 0x0002D480, 0x00013D6C }, // unused
		},
		.ICON0SizeOffset = {
			0x000294F8, // 01G
			0x000294F8, // 02G
			0x000294F8, // 03G
			0x000294F8, // 04G
			0x000294F8, // 05G
			0x000294F8, // unused
			0x000294F8, // unused
			0x000294F8, // unused
			0x000294F8, // unused
		},
		.manualNameCheck = {
			0x0001D9FC, // 01G
			0x0001D9FC, // 02G
			0x0001D9FC, // 03G
			0x0001D9FC, // 04G
			0x0001D9FC, // 05G
			0x0001D9FC, // unused
			0x0001D9FC, // unused
			0x0001D9FC, // unused
			0x0001D9FC, // unused
		},
		.sceMeAudio_67CD7972_NID = 0x902F30D8,
	},
};
#endif

#ifdef CONFIG_371
PatchOffset g_371_offsets = {
	.fw_version = FW_371,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0x0000059C,
		.scePopsManLoadModuleCheck = 0x000000D4,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0002BDA0, 0x00014100 }, // 01G
			{ 0x0002BDA0, 0x00014100 }, // 02G
			{ 0x0002BDA0, 0x00014100 }, // 03G
			{ 0x0002BDA0, 0x00014100 }, // 04G
			{ 0x0002BDA0, 0x00014100 }, // 05G
			{ 0x0002BDA0, 0x00014100 }, // unused
			{ 0x0002BDA0, 0x00014100 }, // unused
			{ 0x0002BDA0, 0x00014100 }, // unused
			{ 0x0002BDA0, 0x00014100 }, // unused
		},
		.ICON0SizeOffset = {
			0x000253F4, // 01G
			0x000253F4, // 02G
			0x000253F4, // 03G
			0x000253F4, // 04G
			0x000253F4, // 05G
			0x000253F4, // unused
			0x000253F4, // unused
			0x000253F4, // unused
			0x000253F4, // unused
		},
		.manualNameCheck = {
			0x0001B044, // 01G
			0x0001B044, // 02G
			0x0001B044, // 03G
			0x0001B044, // 04G
			0x0001B044, // 05G
			0x0001B044, // unused
			0x0001B044, // unused
			0x0001B044, // unused
			0x0001B044, // unused
		},
		.sceMeAudio_67CD7972_NID = 0x902F30D8,
	},
};
#endif

#ifdef CONFIG_352
PatchOffset g_352_offsets = {
	.fw_version = FW_352,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0x00000240,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0002BD20, 0x00013E50 }, // 01G
			{ 0x0002BD20, 0x00013E50 }, // 02G
			{ 0x0002BD20, 0x00013E50 }, // 03G
			{ 0x0002BD20, 0x00013E50 }, // 04G
			{ 0x0002BD20, 0x00013E50 }, // 05G
			{ 0x0002BD20, 0x00013E50 }, // unused
			{ 0x0002BD20, 0x00013E50 }, // unused
			{ 0x0002BD20, 0x00013E50 }, // unused
			{ 0x0002BD20, 0x00013E50 }, // unused
		},
		.ICON0SizeOffset = {
			0x00025080, // 01G
			0x00025080, // 02G
			0x00025080, // 03G
			0x00025080, // 04G
			0x00025080, // 05G
			0x00025080, // unused
			0x00025080, // unused
			0x00025080, // unused
			0x00025080, // unused
		},
		.manualNameCheck = {
			0x0001AF18, // 01G
			0x0001AF18, // 02G
			0x0001AF18, // 03G
			0x0001AF18, // 04G
			0x0001AF18, // 05G
			0x0001AF18, // unused
			0x0001AF18, // unused
			0x0001AF18, // unused
			0x0001AF18, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_351
PatchOffset g_351_offsets = {
	.fw_version = FW_351,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0x000000CC,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0002B240, 0x00013C64 }, // 01G
			{ 0x0002B240, 0x00013C64 }, // 02G
			{ 0x0002B240, 0x00013C64 }, // 03G
			{ 0x0002B240, 0x00013C64 }, // 04G
			{ 0x0002B240, 0x00013C64 }, // 05G
			{ 0x0002B240, 0x00013C64 }, // unused
			{ 0x0002B240, 0x00013C64 }, // unused
			{ 0x0002B240, 0x00013C64 }, // unused
			{ 0x0002B240, 0x00013C64 }, // unused
		},
		.ICON0SizeOffset = {
			0x0001B030, // 01G
			0x0001B030, // 02G
			0x0001B030, // 03G
			0x0001B030, // 04G
			0x0001B030, // 05G
			0x0001B030, // unused
			0x0001B030, // unused
			0x0001B030, // unused
			0x0001B030, // unused
		},
		.manualNameCheck = {
			0x0001C474, // 01G
			0x0001C474, // 02G
			0x0001C474, // 03G
			0x0001C474, // 04G
			0x0001C474, // 05G
			0x0001C474, // unused
			0x0001C474, // unused
			0x0001C474, // unused
			0x0001C474, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_350
PatchOffset g_350_offsets = {
	.fw_version = FW_350,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0x000000CC,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0002B240, 0x00013C64 }, // 01G
			{ 0x0002B240, 0x00013C64 }, // 02G
			{ 0x0002B240, 0x00013C64 }, // 03G
			{ 0x0002B240, 0x00013C64 }, // 04G
			{ 0x0002B240, 0x00013C64 }, // 05G
			{ 0x0002B240, 0x00013C64 }, // unused
			{ 0x0002B240, 0x00013C64 }, // unused
			{ 0x0002B240, 0x00013C64 }, // unused
			{ 0x0002B240, 0x00013C64 }, // unused
		},
		.ICON0SizeOffset = {
			0x0001B030, // 01G
			0x0001B030, // 02G
			0x0001B030, // 03G
			0x0001B030, // 04G
			0x0001B030, // 05G
			0x0001B030, // unused
			0x0001B030, // unused
			0x0001B030, // unused
			0x0001B030, // unused
		},
		.manualNameCheck = {
			0x0001C474, // 01G
			0x0001C474, // 02G
			0x0001C474, // 03G
			0x0001C474, // 04G
			0x0001C474, // 05G
			0x0001C474, // unused
			0x0001C474, // unused
			0x0001C474, // unused
			0x0001C474, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_340
PatchOffset g_340_offsets = {
	.fw_version = FW_340,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0x0000003C,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0002A880, 0x00013850 }, // 01G
			{ 0x0002A880, 0x00013850 }, // 02G
			{ 0x0002A880, 0x00013850 }, // 03G
			{ 0x0002A880, 0x00013850 }, // 04G
			{ 0x0002A880, 0x00013850 }, // 05G
			{ 0x0002A880, 0x00013850 }, // unused
			{ 0x0002A880, 0x00013850 }, // unused
			{ 0x0002A880, 0x00013850 }, // unused
			{ 0x0002A880, 0x00013850 }, // unused
		},
		.ICON0SizeOffset = {
			0x0001A45C, // 01G
			0x0001A45C, // 02G
			0x0001A45C, // 03G
			0x0001A45C, // 04G
			0x0001A45C, // 05G
			0x0001A45C, // unused
			0x0001A45C, // unused
			0x0001A45C, // unused
			0x0001A45C, // unused
		},
		.manualNameCheck = {
			0x0001B8BC, // 01G
			0x0001B8BC, // 02G
			0x0001B8BC, // 03G
			0x0001B8BC, // 04G
			0x0001B8BC, // 05G
			0x0001B8BC, // unused
			0x0001B8BC, // unused
			0x0001B8BC, // unused
			0x0001B8BC, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_330
PatchOffset g_330_offsets = {
	.fw_version = FW_330,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0x0000003C,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0002A000, 0x00013788 }, // 01G
			{ 0x0002A000, 0x00013788 }, // 02G
			{ 0x0002A000, 0x00013788 }, // 03G
			{ 0x0002A000, 0x00013788 }, // 04G
			{ 0x0002A000, 0x00013788 }, // 05G
			{ 0x0002A000, 0x00013788 }, // unused
			{ 0x0002A000, 0x00013788 }, // unused
			{ 0x0002A000, 0x00013788 }, // unused
			{ 0x0002A000, 0x00013788 }, // unused
		},
		.ICON0SizeOffset = {
			0x0001A0D4, // 01G
			0x0001A0D4, // 02G
			0x0001A0D4, // 03G
			0x0001A0D4, // 04G
			0x0001A0D4, // 05G
			0x0001A0D4, // unused
			0x0001A0D4, // unused
			0x0001A0D4, // unused
			0x0001A0D4, // unused
		},
		.manualNameCheck = {
			0x0001B46C, // 01G
			0x0001B46C, // 02G
			0x0001B46C, // 03G
			0x0001B46C, // 04G
			0x0001B46C, // 05G
			0x0001B46C, // unused
			0x0001B46C, // unused
			0x0001B46C, // unused
			0x0001B46C, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_311
PatchOffset g_311_offsets = {
	.fw_version = FW_311,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0xDEADBEEF,
	},
	.pops_patch = {
		.decomp = {
			{ 0x00031D1C, 0x00010794 }, // 01G
			{ 0x00031D1C, 0x00010794 }, // 02G
			{ 0x00031D1C, 0x00010794 }, // 03G
			{ 0x00031D1C, 0x00010794 }, // 04G
			{ 0x00031D1C, 0x00010794 }, // 05G
			{ 0x00031D1C, 0x00010794 }, // unused
			{ 0x00031D1C, 0x00010794 }, // unused
			{ 0x00031D1C, 0x00010794 }, // unused
			{ 0x00031D1C, 0x00010794 }, // unused
		},
		.ICON0SizeOffset = {
			0x0002A640, // 01G
			0x0002A640, // 02G
			0x0002A640, // 03G
			0x0002A640, // 04G
			0x0002A640, // 05G
			0x0002A640, // unused
			0x0002A640, // unused
			0x0002A640, // unused
			0x0002A640, // unused
		},
		.manualNameCheck = {
			0x0001C0C0, // 01G
			0x0001C0C0, // 02G
			0x0001C0C0, // 03G
			0x0001C0C0, // 04G
			0x0001C0C0, // 05G
			0x0001C0C0, // unused
			0x0001C0C0, // unused
			0x0001C0C0, // unused
			0x0001C0C0, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_310
PatchOffset g_310_offsets = {
	.fw_version = FW_310,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0xDEADBEEF,
	},
	.pops_patch = {
		.decomp = {
			{ 0x00031B9C, 0x000105F0 }, // 01G
			{ 0x00031B9C, 0x000105F0 }, // 02G
			{ 0x00031B9C, 0x000105F0 }, // 03G
			{ 0x00031B9C, 0x000105F0 }, // 04G
			{ 0x00031B9C, 0x000105F0 }, // 05G
			{ 0x00031B9C, 0x000105F0 }, // unused
			{ 0x00031B9C, 0x000105F0 }, // unused
			{ 0x00031B9C, 0x000105F0 }, // unused
			{ 0x00031B9C, 0x000105F0 }, // unused
		},
		.ICON0SizeOffset = {
			0x0002A498, // 01G
			0x0002A498, // 02G
			0x0002A498, // 03G
			0x0002A498, // 04G
			0x0002A498, // 05G
			0x0002A498, // unused
			0x0002A498, // unused
			0x0002A498, // unused
			0x0002A498, // unused
		},
		.manualNameCheck = {
			0x0001C0FC, // 01G
			0x0001C0FC, // 02G
			0x0001C0FC, // 03G
			0x0001C0FC, // 04G
			0x0001C0FC, // 05G
			0x0001C0FC, // unused
			0x0001C0FC, // unused
			0x0001C0FC, // unused
			0x0001C0FC, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_303
PatchOffset g_303_offsets = {
	.fw_version = FW_303,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0xDEADBEEF,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0003A08C, 0x00012A60 }, // 01G
			{ 0x0003A08C, 0x00012A60 }, // 02G
			{ 0x0003A08C, 0x00012A60 }, // 03G
			{ 0x0003A08C, 0x00012A60 }, // 04G
			{ 0x0003A08C, 0x00012A60 }, // 05G
			{ 0x0003A08C, 0x00012A60 }, // unused
			{ 0x0003A08C, 0x00012A60 }, // unused
			{ 0x0003A08C, 0x00012A60 }, // unused
			{ 0x0003A08C, 0x00012A60 }, // unused
		},
		.ICON0SizeOffset = {
			0x00032E40, // 01G
			0x00032E40, // 02G
			0x00032E40, // 03G
			0x00032E40, // 04G
			0x00032E40, // 05G
			0x00032E40, // unused
			0x00032E40, // unused
			0x00032E40, // unused
			0x00032E40, // unused
		},
		.manualNameCheck = {
			0xDEADBEEF, // 01G
			0xDEADBEEF, // 02G
			0xDEADBEEF, // 03G
			0xDEADBEEF, // 04G
			0xDEADBEEF, // 05G
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

#ifdef CONFIG_302
PatchOffset g_302_offsets = {
	.fw_version = FW_302,
	.popsman_patch = {
		.get_rif_path = 0xDEADBEEF,
		.get_rif_path_call1 = 0xDEADBEEF,
		.get_rif_path_call2 = 0xDEADBEEF,
		.sceNpDrmGetVersionKeyCall = 0xDEADBEEF,
		.scePspNpDrm_driver_9A34AC9F_Call = 0xDEADBEEF,
		.scePopsManLoadModuleCheck = 0xDEADBEEF,
	},
	.pops_patch = {
		.decomp = {
			{ 0x0003900C, 0x00012314 }, // 01G
			{ 0x0003900C, 0x00012314 }, // 02G
			{ 0x0003900C, 0x00012314 }, // 03G
			{ 0x0003900C, 0x00012314 }, // 04G
			{ 0x0003900C, 0x00012314 }, // 05G
			{ 0x0003900C, 0x00012314 }, // unused
			{ 0x0003900C, 0x00012314 }, // unused
			{ 0x0003900C, 0x00012314 }, // unused
			{ 0x0003900C, 0x00012314 }, // unused
		},
		.ICON0SizeOffset = {
			0x000315CC, // 01G
			0x000315CC, // 02G
			0x000315CC, // 03G
			0x000315CC, // 04G
			0x000315CC, // 05G
			0x000315CC, // unused
			0x000315CC, // unused
			0x000315CC, // unused
			0x000315CC, // unused
		},
		.manualNameCheck = {
			0xDEADBEEF, // 01G
			0xDEADBEEF, // 02G
			0xDEADBEEF, // 03G
			0xDEADBEEF, // 04G
			0xDEADBEEF, // 05G
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
			0xDEADBEEF, // unused
		},
		.sceMeAudio_67CD7972_NID = 0xFC56480E,
	},
};
#endif

PatchOffset *g_offs = NULL;

void setup_patch_offset_table(u32 fw_version)
{
#ifdef CONFIG_639
	if(fw_version == g_639_offsets.fw_version) {
		g_offs = &g_639_offsets;
	}
#endif

#ifdef CONFIG_635
	if(fw_version == g_635_offsets.fw_version) {
		g_offs = &g_635_offsets;
	}
#endif

#ifdef CONFIG_620
   	if(fw_version == g_620_offsets.fw_version) {
		g_offs = &g_620_offsets;
	}
#endif

#ifdef CONFIG_610
   	if(fw_version == g_610_offsets.fw_version) {
		g_offs = &g_610_offsets;
	}
#endif

#ifdef CONFIG_600
   	if(fw_version == g_600_offsets.fw_version) {
		g_offs = &g_600_offsets;
	}
#endif

#ifdef CONFIG_551
   	if(fw_version == g_551_offsets.fw_version) {
		g_offs = &g_551_offsets;
	}
#endif

#ifdef CONFIG_550
   	if(fw_version == g_550_offsets.fw_version) {
		g_offs = &g_550_offsets;
	}
#endif

#ifdef CONFIG_503
   	if(fw_version == g_503_offsets.fw_version) {
		g_offs = &g_503_offsets;
	}
#endif

#ifdef CONFIG_501
   	if(fw_version == g_501_offsets.fw_version) {
		g_offs = &g_501_offsets;
	}
#endif

#ifdef CONFIG_500
   	if(fw_version == g_500_offsets.fw_version) {
		g_offs = &g_500_offsets;
	}
#endif

#ifdef CONFIG_400
   	if(fw_version == g_400_offsets.fw_version) {
		g_offs = &g_400_offsets;
	}
#endif

#ifdef CONFIG_373
   	if(fw_version == g_373_offsets.fw_version) {
		g_offs = &g_373_offsets;
	}
#endif

#ifdef CONFIG_371
   	if(fw_version == g_371_offsets.fw_version) {
		g_offs = &g_371_offsets;
	}
#endif

#ifdef CONFIG_352
   	if(fw_version == g_352_offsets.fw_version) {
		g_offs = &g_352_offsets;
	}
#endif

#ifdef CONFIG_351
   	if(fw_version == g_351_offsets.fw_version) {
		g_offs = &g_351_offsets;
	}
#endif

#ifdef CONFIG_350
   	if(fw_version == g_350_offsets.fw_version) {
		g_offs = &g_350_offsets;
	}
#endif

#ifdef CONFIG_340
   	if(fw_version == g_340_offsets.fw_version) {
		g_offs = &g_340_offsets;
	}
#endif

#ifdef CONFIG_330
   	if(fw_version == g_330_offsets.fw_version) {
		g_offs = &g_330_offsets;
	}
#endif

#ifdef CONFIG_311
   	if(fw_version == g_311_offsets.fw_version) {
		g_offs = &g_311_offsets;
	}
#endif

#ifdef CONFIG_310
   	if(fw_version == g_310_offsets.fw_version) {
		g_offs = &g_310_offsets;
	}
#endif

#ifdef CONFIG_303
   	if(fw_version == g_303_offsets.fw_version) {
		g_offs = &g_303_offsets;
	}
#endif

#ifdef CONFIG_302
   	if(fw_version == g_302_offsets.fw_version) {
		g_offs = &g_302_offsets;
	}
#endif
}
