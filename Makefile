export CC = gcc

export LIBHEADERLOC = include
export TARGET
export LIBLOCATION
export LIBNAME
export LIBHEADERLOC
export APPLOCATION
export APPNAME
export CFLAGS


queue : TARGET = queue
queue : LIBLOCATION = lib/$(TARGET)
queue : APPLOCATION = app/$(TARGET)
queue : LIBNAME = queue
queue : APPNAME = queue_ll
queue : generalbuild

rebuild_queue : reconfigure_queue queue

generalbuild : CFLAGS = -O3 -w -I$(LIBHEADERLOC) -L$(LIBLOCATION)
generalbuild :
	@bash scripts/loadconfig.sh configs/queue_defconfig include/queue_config.h
	@make -f lib/Makefile
	@make -f app/Makefile
	@ln -sf $(APPLOCATION)/$(APPNAME).out ./$(APPNAME).out

reconfigure_queue :
	@bash scripts/createconfig.sh desc/queue.desc configs/queue_defconfig
