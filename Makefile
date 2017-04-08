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
queue : APPNAME = queue_ll
queue : generalbuild

rebuild_queue : reconfigure_queue queue

stack : TARGET = stack
stack : LIBLOCATION = $(TARGET)
stack : APPLOCATION = $(TARGET)
stack : LIBNAME = stack
stack : APPNAME = stack_ll
stack : generalbuild

generalbuild : CFLAGS = -O3 -w -I$(LIBHEADERLOC) -L$(CURDIR)/lib/$(LIBLOCATION)
generalbuild :
	@echo Creating header from config file..
	@bash $(CURDIR)/scripts/loadconfig.sh $(CONFIG) $(CONFIG_HEADER)
	@echo Making library..
	@$(MAKE) -C lib
	@echo Making app..
	@$(MAKE) -C app
	@echo Creating shortcut..
	@ln -sf $(CURDIR)/app/$(APPLOCATION)/$(APPNAME).out $(CURDIR)/$(APPNAME).out
	@echo "Don't forget to add library paths before running the program!"

reconfigure_queue :
	@bash $(CURDIR)/scripts/createconfig.sh desc/queue.desc configs/queue_defconfig
