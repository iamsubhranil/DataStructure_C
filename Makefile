export CC = gcc

export LIBHEADERLOC = $(CURDIR)/include
export TARGET
export LIBLOCATION
export LIBNAME
export LIBHEADERLOC
export APPLOCATION
export APPNAME
export CFLAGS

queue : TARGET = queue
queue : LIBLOCATION = $(TARGET)
queue : APPLOCATION = $(TARGET)
queue : LIBNAME = queue
queue : CONFIG=$(CURDIR)/configs/queue_defconfig
queue : CONFIG_HEADER=$(CURDIR)/include/queue_config.h
queue : CUSTOMSCRIPT = $(CURDIR)/scripts/queueconfig.sh
queue : APPNAME = queue_ll
queue : generalbuild

reconfigure_queue : DESCFILE = $(CURDIR)/desc/queue.desc
reconfigure_queue : DEFCONFIG = $(CURDIR)/configs/queue_defconfig
reconfigure_queue : general_reconfig
rebuild_queue : reconfigure_queue queue

stack : TARGET = stack
stack : LIBLOCATION = $(TARGET)
stack : APPLOCATION = $(TARGET)
stack : LIBNAME = stack
stack : APPNAME = stack_ll
stack : CONFIG = $(CURDIR)/configs/stack_defconfig
stack : CONFIG_HEADER = $(CURDIR)/include/stack_config.h
stack : generalbuild

reconfigure_stack : DESCFILE = $(CURDIR)/desc/stack.desc
reconfigure_stack : DEFCONFIG = $(CURDIR)/configs/stack_defconfig
reconfigure_stack : general_reconfig
rebuild_stack : reconfigure_stack stack

linkedlist : TARGET = linkedlist
linkedlist : LIBLOCATION = $(TARGET)
linkedlist : APPLOCATION = $(TARGET)
linkedlist : LIBNAME = linkedlist
linkedlist : APPNAME = ll_frontend
linkedlist : CONFIG = $(CURDIR)/configs/linkedlist_defconfig
linkedlist : CONFIG_HEADER = $(CURDIR)/include/linkedlist_config.h
linkedlist : generalbuild

reconfigure_linkedlist : DESCFILE = $(CURDIR)/desc/linkedlist.desc
reconfigure_linkedlist : DEFCONFIG = $(CURDIR)/configs/linkedlist_defconfig
reconfigure_linkedlist : general_reconfig
rebuild_linkedlist : reconfigure_linkedlist linkedlist

generalbuild : CFLAGS = -O3 -w -I$(LIBHEADERLOC) -L$(CURDIR)/lib/$(LIBLOCATION)
generalbuild :
	@echo Creating header from config file..
	@bash $(CURDIR)/scripts/loadconfig.sh $(CONFIG) $(CONFIG_HEADER) $(CUSTOMSCRIPT)
	@echo Making library..
	@$(MAKE) -C lib
	@echo Making app..
	@$(MAKE) -C app
	@echo Creating shortcut..
	@ln -sf $(CURDIR)/app/$(APPLOCATION)/$(APPNAME).out $(CURDIR)/$(APPNAME).out
	@echo Compilation successful!

general_reconfig :
	@bash $(CURDIR)/scripts/createconfig.sh $(DESCFILE) $(DEFCONFIG)
