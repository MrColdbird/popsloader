#ifndef POPSLOADER_H
#define POPSLOADER_H

enum {
	TARGET_ORIG = 0,
	TARGET_620,
	TARGET_635,
	TARGET_639,
};

struct popsloader_config {
	int target_type;
};

extern struct popsloader_config g_conf;

int save_config(void);
int load_config(void);

#define BASE_PATH "0:/seplugins/popsloader/"
#define MODULE_PATH BASE_PATH "modules/"
#define CFG_PATH BASE_PATH "pops.cfg"

#endif
