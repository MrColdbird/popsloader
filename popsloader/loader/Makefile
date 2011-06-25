TARGET = popsloader
OBJS = main.o ../common/utils.o ../common/vsnprintf.o ../common/conf.o

#PRO_HOME = d:/PSP/635PRO

CFLAGS = -Os -G0 -Wall -I../common -I$(PRO_HOME)/include -I$(PRO_HOME)/Common

ifeq ($(DEBUG), 1)
CFLAGS += -DDEBUG=1
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
