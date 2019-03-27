
obj-m += helloworld.o helloworld_with_pars.o helloworld_with_timing.o

KERNEL_DIR ?= $(RPI_LINUX_SOURCE)

all:
	make -C $(KERNEL_DIR) \
		ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
		SUBDIRS=$(PWD) modules

clean: 
	make -C $(KERNEL_DIR) \
		ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- \
		SUBDIRS=$(PWD) clean

deploy:
	scp *.ko pi@192.168.0.12:

