obj-m += hello_cdev.o

KVERSION := $(shell uname -r)
PWD := $(shell pwd)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
