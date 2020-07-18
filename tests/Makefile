TARGET = test_module
obj-m = ${TARGET}ko.o
${TARGET}ko-objs := ${TARGET}.o

KVERSION = $(shell uname -r)
all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
