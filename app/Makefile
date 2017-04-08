all : cleantarget buildtarget
	@echo Compilation complete!

buildtarget : $(APPLOCATION)/$(APPNAME).c
	@echo Compiling target..
	@$(CC) $(CFLAGS) $(APPLOCATION)/$(APPNAME).c -l$(LIBNAME) $(GENERICLIB) -o $(APPLOCATION)/$(APPNAME).out

cleantarget :
	@echo Removing compiled target..
	@$(RM) $(APPLOCATION)/$(TARGET).out
