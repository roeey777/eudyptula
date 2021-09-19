LINUX_DIR ?= /lib/modules/$(shell uname -r)/build

ifneq ($(BR2_EXTERNAL_EUDYPTULA_PATH),)
OBJS := $(addsuffix .o, $(notdir $(basename $(wildcard $(BR2_EXTERNAL_EUDYPTULA_PATH)/package/solution-4/*.c))))
else
OBJS := solution_4.o
endif

obj-m += $(OBJS)

.PHONEY: all install clean

all: modules

modules:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' modules

install: modules
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' modules_install

clean:
	$(MAKE) -C '$(LINUX_DIR)' M='$(PWD)' clean
