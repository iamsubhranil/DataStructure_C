CC = gcc

TARGET = queue_ll

LIBFILENAME = queue_lib
LIBHEADERNAME = queue_interface
LIBHEADERLOC = .
LIBNAME = queue
LIBLOCATION = .

CFLAGS = -I$(LIBHEADERLOC) -L$(LIBLOCATION)

all : clean buildlib $(TARGET)
	@echo Make complete!

buildtarget : cleantarget $(TARGET)

buildlib : cleanlib $(LIBLOCATION)/$(LIBFILENAME).c $(LIBHEADERLOC)/$(LIBHEADERNAME).h
	@echo Compiling library sources..
	@$(CC) $(CFLAGS) -c -Werror -fPIC $(LIBFILENAME).c
	@echo Creating shared libraries..
	@$(CC) -shared -o lib$(LIBNAME).so $(LIBFILENAME).o
	@echo Removing object files..
	@$(RM) $(LIBFILENAME).o

$(TARGET) : $(TARGET).c
	@echo Compiling target..
	@$(CC) $(CFLAGS) $(TARGET).c -l$(LIBNAME) -o $(TARGET).out

clean: cleantarget cleanlib

cleantarget :
	@echo Removing compiled target..
	@$(RM) $(TARGET).out

cleanlib :
	@echo Removing shared libraries..
	@$(RM) $(LIBFILENAME).o
	@$(RM) lib$(LIBNAME).so
