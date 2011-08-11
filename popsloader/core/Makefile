TARGET = popscore
OBJS = main.o resolve_nid.o resolve_nid_impose.o impose_patch.o replace_module.o ../common/libs.o ../common/conf.o

OBJS += nid_660_to_620.o \
		nid_660_to_635.o \
		nid_635_to_620.o \
		nid_635_to_639.o \
		nid_620_to_635.o \
		nid_500_to_635.o \
		nid_500_to_620.o \
		nid_400_to_620.o \
		nid_400_to_635.o \
		nid_373_to_620.o \
		nid_373_to_635.o \
		nid_393_to_620.o \
		nid_393_to_635.o \
		nid_impose_400_to_620.o \
		nid_impose_400_to_635.o

#PRO_HOME = d:/PSP/635PRO

CFLAGS = -Os -G0 -Wall -I../common -I$(PRO_HOME)/include -I$(PRO_HOME)/Common

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG=1
OBJS += $(PRO_HOME)/Common/utils.o $(PRO_HOME)/Common/printk.o
else
OBJS += ../common/utils.o ../common/vsnprintf.o
endif

LDFLAGS = -mno-crt0 -nostartfiles -L. -L $(PRO_HOME)/libs
LIBS = -lpspsystemctrl_kernel -lpspkubridge
PSP_FW_VERSION=620
PRX_EXPORTS = exports.exp

BUILD_PRX=1
USE_KERNEL_LIBS=1
USE_KERNEL_LIBC=1

PSPSDK = $(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
