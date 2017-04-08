export CC = gcc

export LIBHEADERLOC = include
export TARGET
export LIBLOCATION
export LIBNAME
export LIBHEADERLOC
export APPLOCATION
export APPNAME
export CFLAGS
export GENERICLIB

queue : TARGET = queue
queue : LIBLOCATION = lib/$(TARGET)
queue : APPLOCATION = app/$(TARGET)
queue : LIBNAME = queue
queue : APPNAME = queue_ll
queue : GENERICLIB = -lgeneric
queue : generalbuild

rebuild_queue : reconfigure_queue queue

generalbuild : CFLAGS = -O3 -w -I$(LIBHEADERLOC) -L$(LIBLOCATION) -Llib
generalbuild :
	@echo Creating header from config file..
	@bash scripts/loadconfig.sh configs/queue_defconfig include/queue_config.h
	@echo Making library..
	@make -f lib/Makefile
	@echo Making app..
	@make -f app/Makefile
	@echo Creating shortcut..
	@ln -sf $(APPLOCATION)/$(APPNAME).out ./$(APPNAME).out

reconfigure_queue :
	@bash scripts/createconfig.sh desc/queue.desc configs/queue_defconfig
