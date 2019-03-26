ifneq ($(KERNELRELEASE),)
	obj-m := scull.o
	
else
	KERNELDIR ?= /home/michael/learningDeviceDriver/rpilinux
	PWD := $(shell pwd)
	
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
