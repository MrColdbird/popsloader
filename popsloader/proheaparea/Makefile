TARGET = proheaparea
OBJS = main.o imports.o

CFLAGS = -Os -G0 -Wall -I. -I ~/635PRO/Common -I ~/635PRO/include -fno-toplevel-reorder -nostartfiles
PSP_FW_VERSION=635 
BUILD_PRX=1

PRX_EXPORTS = exports.exp

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
