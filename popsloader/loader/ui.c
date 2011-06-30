#include <pspkernel.h>
#include <pspreg.h>
#include <stdio.h>
#include <string.h>
#include <pspsysmem_kernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <psppower.h>
#include "utils.h"
#include "main.h"

struct MenuItem {
	char *name;
	u32 pops_fw_version;
};

struct Menu {
	char *banner;
	int cur_sel;
	struct MenuItem *items;
	int size;
};

#define MAX_SCREEN_X 68
#define MAX_SCREEN_Y 33
#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)
#define PIXEL_SIZE (4)
#define FRAME_SIZE (BUF_WIDTH * SCR_HEIGHT * PIXEL_SIZE)
#define CTRL_DELAY   100000
#define CTRL_DEADZONE_DELAY 500000
#define DRAW_BUF (void*)(0x44000000)
#define DISPLAY_BUF (void*)(0x44000000 + FRAME_SIZE)

#define printf pspDebugScreenPrintf

static u32 g_last_btn = 0;
static u32 g_last_tick = 0;
static u32 g_deadzone_tick = 0;

int g_display_flip;

void *get_drawing_buffer(void)
{
	void *buffer;

	if(g_display_flip) {
		buffer = DRAW_BUF;
	} else {
		buffer = DISPLAY_BUF;
	}

	return buffer;
}

void *get_display_buffer(void)
{
	void *buffer;

	if(g_display_flip) {
		buffer = DISPLAY_BUF;
	} else {
		buffer = DRAW_BUF;
	}

	return buffer;
}

void frame_start(void)
{
	scePowerTick(0);
	sceDisplayWaitVblank();
	pspDebugScreenSetOffset((int)get_drawing_buffer() - 0x44000000);
	memset(get_drawing_buffer(), 0, 512*272*4);
}

void frame_end(void)
{
	g_display_flip = !g_display_flip;
	sceDisplaySetFrameBuf(get_display_buffer(), 512, PSP_DISPLAY_PIXEL_FORMAT_8888, PSP_DISPLAY_SETBUF_NEXTFRAME);
	sceDisplayWaitVblank();
}

u32 ctrl_read(void)
{
	SceCtrlData ctl;

	sceCtrlReadBufferPositive(&ctl, 1);

	if (ctl.Buttons == g_last_btn) {
		if (ctl.TimeStamp - g_deadzone_tick < CTRL_DEADZONE_DELAY) {
			return 0;
		}

		if (ctl.TimeStamp - g_last_tick < CTRL_DELAY) {
			return 0;
		}

		g_last_tick = ctl.TimeStamp;

		return g_last_btn;
	}

	g_last_btn = ctl.Buttons;
	g_deadzone_tick = g_last_tick = ctl.TimeStamp;

	return g_last_btn;
}

static void set_screen_xy(int x, int y)
{
	pspDebugScreenSetXY(x, y);
}

static void set_color(u32 color)
{
	pspDebugScreenSetTextColor(color);
}

void menu_draw(struct Menu *menu)
{
	int i;

	set_screen_xy((MAX_SCREEN_X - strlen(menu->banner)) / 2, 2);
	printf("%s\n", menu->banner);

	for(i=0; i<menu->size; ++i) {
		set_screen_xy((MAX_SCREEN_X - strlen(menu->items[i].name)) / 2, 5 + i);

		if(i == menu->cur_sel) {
			set_color(0x000000FF);
		}

		printf("%s\n", menu->items[i].name);
		set_color(0xFFFFFFFF);
	}
}

int menu_ctrl(struct Menu *menu)
{
	u32 key;

	key = ctrl_read();

	if(key & PSP_CTRL_UP) {
		if(menu->cur_sel > 0) {
			menu->cur_sel--;
		} else {
			menu->cur_sel = menu->size - 1;
		}
	}

	if(key & PSP_CTRL_DOWN) {
		if(menu->cur_sel < menu->size - 1) {
			menu->cur_sel++;
		} else {
			menu->cur_sel = 0;
		}
	}

	if(key & PSP_CTRL_CIRCLE || key & PSP_CTRL_CROSS) {
		return 1;
	}

	return 0;
}

struct MenuItem main_menu_items[] = {
	{ "3.02 pops", FW_302, },
	{ "3.03 pops", FW_303, },
	{ "3.10 pops", FW_310, },
	{ "3.11 pops", FW_311, },
	{ "3.30 pops", FW_330, },
	{ "3.40 pops", FW_340, },
	{ "3.50 pops", FW_350, },
	{ "3.51 pops", FW_351, },
	{ "3.52 pops", FW_352, },
	{ "3.71 pops", FW_371, },
	{ "3.72 pops", FW_372, },
	{ "3.80 pops", FW_380, },
	{ "3.90 pops", FW_390, },
	{ "3.93 pops", FW_393, },
	{ "3.96 pops", FW_396, },
	{ "4.00 pops", FW_401, },
	{ "5.00 pops", FW_500, },
	{ "5.01 pops", FW_501, },
	{ "5.03 pops", FW_503, },
	{ "5.50 pops", FW_550, },
	{ "5.51 pops", FW_551, },
	{ "6.00 pops", FW_600, },
	{ "6.10 pops", FW_610, },
	{ "6.20 pops", FW_620, },
	{ "6.35 pops", FW_635, },
	{ "6.39 pops", FW_639, },
	{ "Original from flash", 0, },
};

struct Menu main_menu = {
	"Please select your POPS version:",
	0,
	main_menu_items,
	NELEMS(main_menu_items),
};

int get_corrspending_fw(u32 fw_version)
{
	size_t i;

	for(i=0; i<main_menu.size-1; ++i) {
		if(main_menu.items[i].pops_fw_version == fw_version)
			return i;
	}

	return main_menu.size - 1;
}

int get_pops_fw_version(u32 *fw_version)
{
	int is_done = 0, ret;

	printk("%s: started\n", __func__);
	pspDebugScreenInit();

	main_menu.cur_sel = get_corrspending_fw(*fw_version);

	while (!is_done) {
		frame_start();
		menu_draw(&main_menu);
		ret = menu_ctrl(&main_menu);

		if(ret != 0) {
			is_done = 1;
		}

		frame_end();
	}

	*fw_version = main_menu.items[main_menu.cur_sel].pops_fw_version;

	return 0;
}
