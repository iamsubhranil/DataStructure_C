CC = gcc

TARGET = queue_ll

LIBFILENAME = queue_lib
LIBHEADERNAME = queue_interface
LIBHEADERLOC = .
LIBNAME = queue
LIBLOCATION = .

PERCEN=0

CFLAGS = -g -O2 -w -I$(LIBHEADERLOC) -L$(LIBLOCATION)

export LD_LIBRARY_PATH=$(LIBLOCATION):$LD_LIBRARY_PATH

all : clean reconfigure buildlib $(TARGET)
	@echo XXX
	@echo 100
	@echo Compilation complete!
	@echo XXX

reconfigure : ./loadconfig.sh
	@./loadconfig.sh defconfig config.h

debugbuild : CFLAGS+= -g
debugbuild : all

menuconfig : ./queue_menuconfig.sh
	@./queue_menuconfig.sh

buildtarget : cleantarget $(TARGET)

buildlib : cleanlib $(LIBLOCATION)/$(LIBFILENAME).c $(LIBHEADERLOC)/$(LIBHEADERNAME).h
	@echo XXX
	@echo 30
	@echo Compiling library sources..
	@echo XXX
	@$(CC) $(CFLAGS) -c -Werror -fPIC $(LIBFILENAME).c
	@echo XXX
	@echo 60
	@echo Creating shared libraries..
	@echo XXX
	@$(CC) -shared -o lib$(LIBNAME).so $(LIBFILENAME).o
	@echo XXX
	@echo 80
	@echo Removing object files..
	@echo XXX
	@$(RM) $(LIBFILENAME).o

$(TARGET) : $(TARGET).c
	@echo XXX
	@echo 90
	@echo Compiling target..
	@echo XXX
	@$(CC) $(CFLAGS) $(TARGET).c -l$(LIBNAME) -o $(TARGET).out

clean: cleantarget cleanlib

cleantarget :
	@echo XXX
	@echo 0
	@echo Removing compiled target..
	@echo XXX
	@$(RM) $(TARGET).out

cleanlib :
	@echo XXX
	@echo 10
	@echo Removing shared libraries..
	@echo XXX
	@$(RM) $(LIBFILENAME).o
	@$(RM) lib$(LIBNAME).so
