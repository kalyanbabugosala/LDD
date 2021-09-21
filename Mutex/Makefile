obj-m+= Mutex.o
#obj-m is used to build as module
#obj-y is used to build as statically
KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(shell pwd) modules
clean:
	make -C $(KDIR) M=$(shell pwd) clean
