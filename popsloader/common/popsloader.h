#ifndef POPSLOADER_H
#define POPSLOADER_H

struct pops_file_struct {
	char fn[256];
	int type;
};

enum {
	TARGET_ORIG = 0,
	TARGET_620,
	TARGET_635,
	TARGET_639,
};

#define BASE_PATH "0:/seplugins/popsloader/"
#define MODULE_PATH BASE_PATH "modules/"
#define CFG_PATH BASE_PATH "pops.cfg"

#endif
