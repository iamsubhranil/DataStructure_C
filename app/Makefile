all : clean $(TARGET)
	@echo Compilation complete!
	@echo Run the following command before running the program :
	@bash scripts/addenv.sh

debugbuild : CFLAGS+= -g
debugbuild : all

buildtarget : cleantarget $(TARGET)

$(TARGET) : $(APPLOCATION)/$(APPNAME).c
	@echo Compiling target..
	@$(CC) $(CFLAGS) $(APPLOCATION)/$(APPNAME).c -l$(LIBNAME) $(GENERICLIB) -o ./$(APPLOCATION)/$(APPNAME).out

clean: cleantarget

cleantarget :
	@echo Removing compiled target..
	@$(RM) $(APPLOCATION)/$(TARGET).out
