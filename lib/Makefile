LIBFILENAME = $(TARGET)_lib
LIBHEADERNAME = $(TARGET)_interface
LIBNAME = $(TARGET)

buildlib : cleanlib $(LIBLOCATION)/$(LIBFILENAME).c $(LIBHEADERLOC)/$(LIBHEADERNAME).h
	@echo Compiling library sources..
	@$(CC) $(CFLAGS) -c -Werror -fPIC $(LIBLOCATION)/$(LIBFILENAME).c -o $(LIBLOCATION)/$(LIBFILENAME).o
	@echo Creating shared libraries..
	@$(CC) -shared -o  $(LIBLOCATION)/lib$(LIBNAME).so $ $(LIBLOCATION)/$(LIBFILENAME).o
	@echo Removing object files..
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o
	
cleanlib :
	@echo Removing shared libraries..
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o
	@$(RM) $(LIBLOCATION)/lib$(LIBNAME).so

reconfigure : scripts/loadconfig.sh
	@bash scripts/loadconfig.sh queue_defconfig queue_config  .h

