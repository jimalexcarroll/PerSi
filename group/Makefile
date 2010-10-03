EXTRA_CFLAGS += -I$(LDDINCDIR) -D__DEBUG_TRACE__

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-y += ../mapmanager/ ../devicesimulator/ ../drivers/

else

KERNELDIR := /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

default: ../mapmanager/persi
	$(MAKE) -C $(KERNELDIR) M=$(PWD) LDDINCDIR=$(PWD)/../include modules

.PHONY: install
install: 
	# Move binaries to build folder
	# Map Manager
	mv -f ../mapmanager/mapmanager.ko ../build
	mv -f ../mapmanager/mapmanager.mod.c ../build
	mv -f ../mapmanager/mapmanager.mod.o ../build
	mv -f ../mapmanager/mapmanager.o ../build

	# Device Simulator
	mv -f ../devicesimulator/examplesimulator.ko ../build
	mv -f ../devicesimulator/examplesimulator.mod.c ../build	
	mv -f ../devicesimulator/examplesimulator.mod.o ../build	
	mv -f ../devicesimulator/examplesimulator.o ../build

        # Drivers
	mv -f ../drivers/exampledriver.ko ../build
	mv -f ../drivers/exampledriver.mod.c ../build	
	mv -f ../drivers/exampledriver.mod.o ../build	
	mv -f ../drivers/exampledriver.o ../build

	# Command line
	mv -f ../mapmanager/persi ../build

	# Copy scripts to build folder
	cp -f ../scripts/persi_load ../build
	cp -f ../scripts/persi_unload ../build

.PHONY: clean
clean:
	# Remove binaries from build folder(s)
	rm -f modules.order
	rm -f Module.symvers

	# Map Manager
	rm -f ../build/mapmanager.ko
	rm -f ../build/mapmanager.mod.c 
	rm -f ../build/mapmanager.mod.o 
	rm -f ../build/mapmanager.o 
	rm -f ../mapmanager/modules.order
	rm -f ../mapmanager/Module.symvers

	# Command Line Interface
	rm -f ../build/persi

	# Device Simulator
	rm -f ../build/examplesimulator.ko
	rm -f ../build/examplesimulator.mod.c 
	rm -f ../build/examplesimulator.mod.o 
	rm -f ../build/examplesimulator.o 
	rm -f ../devicesimulator/modules.order 
	rm -f ../devicesimulator/Module.symvers 

	# Drivers
	rm -f ../build/exampledriver.ko
	rm -f ../build/exampledriver.mod.c 
	rm -f ../build/exampledriver.mod.o 
	rm -f ../build/exampledriver.o 
	rm -f ../drivers/modules.order 
	rm -f ../drivers/Module.symvers 

	# Remove exported scripts
	rm -f ../build/persi_load
	rm -f ../build/persi_unload

../mapmanager/persi:
	cc ../mapmanager/mapmanageruser.c -o ../mapmanager/persi -I../include


endif




