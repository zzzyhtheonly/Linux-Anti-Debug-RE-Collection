TARGET = chk_hbreak
obj-m := ${TARGET}ko.o
${TARGET}ko-objs := ${TARGET}.o ../headers/headers.o
ccflags-y = -I$(PWD)/../headers

KVERSION = $(shell uname -r)
all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) $(MAKE_OPTS) modules
clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) $(MAKE_OPTS) clean
