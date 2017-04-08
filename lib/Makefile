LIBFILENAME = $(TARGET)_lib
LIBHEADERNAME = $(TARGET)_interface
LIBNAME = $(TARGET)

buildlib : cleanlib $(LIBLOCATION)/$(LIBFILENAME).c $(LIBHEADERLOC)/$(LIBHEADERNAME).h
	@echo Compiling generic libraries..
	@$(CC) $(CFLAGS) -c -Werror -fPIC -o lib/generic.o lib/status.c
	@$(CC) -shared -o lib/libgeneric.so lib/generic.o
	@$(RM) lib/*.o
	@echo Compiling library sources..
	@$(CC) $(CFLAGS) -c -Werror -fPIC $(LIBLOCATION)/$(LIBFILENAME).c -o $(LIBLOCATION)/$(LIBFILENAME).o
	@echo Creating shared libraries..
	@$(CC) -shared -o  $(LIBLOCATION)/lib$(LIBNAME).so $(LIBLOCATION)/$(LIBFILENAME).o
	@echo Removing object files..
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o
	
cleanlib :
	@echo Removing shared libraries..
	@$(RM) $(LIBLOCATION)/$(LIBFILENAME).o
	@$(RM) $(LIBLOCATION)/lib$(LIBNAME).so

