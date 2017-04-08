LIBFILENAME = $(TARGET)_lib
LIBHEADERNAME = $(TARGET)_interface
LIBNAME = $(TARGET)

buildlib : cleanlib $(LIBLOCATION)/$(LIBFILENAME).c
	@echo Compiling generic libraries..
	@$(CC) $(CFLAGS) -c -Werror -fPIC status.c node.c
	@echo Compiling library sources..
	@$(CC) $(CFLAGS) -c -Werror -fPIC $(LIBLOCATION)/$(LIBFILENAME).c -o $(LIBLOCATION)/$(LIBFILENAME).o
	@echo Creating shared library..
	@$(CC) -shared -o  $(LIBLOCATION)/lib$(LIBNAME).so $(LIBLOCATION)/$(LIBFILENAME).o node.o status.o
	@echo Removing object files..
	@$(RM) node.o status.o $(LIBLOCATION)/$(LIBFILENAME).o
	
cleanlib :
	@echo Removing shared libraries..
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o
	@$(RM) $(LIBLOCATION)/lib$(LIBNAME).so

