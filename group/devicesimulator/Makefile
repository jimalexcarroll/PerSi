EXTRA_CFLAGS += -I$(LDDINCDIR) -D__DEBUG_TRACE__

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	:= ../../devicesimulator/examplesimulator.o
examplesimulator-objs    :- ../../build/mapmanager.o

else

KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) LDDINCDIR=$(PWD)/../../include modules

endif
