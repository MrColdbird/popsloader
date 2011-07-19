#ifndef POPSLOADER_H
#define POPSLOADER_H

#define POPSLOADER_VERSION_STR "New popsloader v2"

struct popsloader_config {
	u32 pops_fw_version;
};

extern struct popsloader_config g_conf;

int save_config(void);
int load_config(void);
void def_config(struct popsloader_config *conf);

#define BASE_PATH "0:/seplugins/popsloader/"
#define MODULE_PATH BASE_PATH "modules/"
#define CFG_PATH BASE_PATH "pops.cfg"

#endif
