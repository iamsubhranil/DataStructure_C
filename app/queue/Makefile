TARGET = queue_ll

LIBFILENAME = queue_lib
LIBHEADERNAME = queue_interface
LIBNAME = queue

all : clean reconfigure buildlib $(TARGET)
	@echo Compilation complete!
	@echo Run the following command before running the program :
	@bash scripts/addenv.sh

reconfigure : scripts/loadconfig.sh
	@bash scripts/loadconfig.sh queue_defconfig queue_config.h

debugbuild : CFLAGS+= -g
debugbuild : all

menuconfig : ./queue_menuconfig.sh
	@bash queue_menuconfig.sh

buildtarget : cleantarget $(TARGET)

buildlib : cleanlib $(LIBLOCATION)/$(LIBFILENAME).c $(LIBHEADERLOC)/$(LIBHEADERNAME).h
	@echo Compiling library sources..
	@$(CC) $(CFLAGS) -c -Werror -fPIC $(LIBLOCATION)/$(LIBFILENAME).c -o $(LIBLOCATION)/$(LIBFILENAME).o
	@echo Creating shared libraries..
	@$(CC) -shared -o $(LIBLOCATION)/lib$(LIBNAME).so $(LIBLOCATION)/$(LIBFILENAME).o
	@echo Removing object files..
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o

$(TARGET) : ./app/queue/queue_ll.c
	@echo Compiling target..
	@$(CC) $(CFLAGS) ./app/queue/$(TARGET).c -l$(LIBNAME) -o ./app/queue/$(TARGET).out

clean: cleantarget cleanlib

cleantarget :
	@echo Removing compiled target..
	@$(RM) $(TARGET).out

cleanlib :
	@echo Removing shared libraries..
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o
	@$(RM) $(LIBLOCATION)/lib$(LIBNAME).so
