TARGET = queue_ll

LIBFILENAME = queue_lib
LIBHEADERNAME = queue_interface
LIBNAME = queue

all : clean reconfigure buildlib $(TARGET)
	@echo XXX
	@echo 100
	@echo Compilation complete!
	@echo XXX
	@echo Run the following command before running the program :
	@bash addenv.sh

reconfigure : ./loadconfig.sh
	@bash loadconfig.sh queue_defconfig queue_config.h

debugbuild : CFLAGS+= -g
debugbuild : all

menuconfig : ./queue_menuconfig.sh
	@bash queue_menuconfig.sh

buildtarget : cleantarget $(TARGET)

buildlib : cleanlib $(LIBLOCATION)/$(LIBFILENAME).c $(LIBHEADERLOC)/$(LIBHEADERNAME).h
	@echo XXX
	@echo 30
	@echo Compiling library sources..
	@echo XXX
	@$(CC) $(CFLAGS) -c -Werror -fPIC $(LIBLOCATION)/$(LIBFILENAME).c -o $(LIBLOCATION)/$(LIBFILENAME).o
	@echo XXX
	@echo 60
	@echo Creating shared libraries..
	@echo XXX
	@$(CC) -shared -o $(LIBLOCATION)/lib$(LIBNAME).so $(LIBLOCATION)/$(LIBFILENAME).o
	@echo XXX
	@echo 80
	@echo Removing object files..
	@echo XXX
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o

$(TARGET) : ./app/queue/queue_ll.c
	@echo XXX
	@echo 90
	@echo Compiling target..
	@echo XXX
	@$(CC) $(CFLAGS) ./app/queue/$(TARGET).c -l$(LIBNAME) -o ./app/queue/$(TARGET).out

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
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o
	@$(RM) $(LIBLOCATION)/lib$(LIBNAME).so
