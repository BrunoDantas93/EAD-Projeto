PROJ_NAME = Example

PROJ_MAIN_File = main.c

C_SOURCE = $(wildcard ./src/func/*.c) 

H_SOURCE = $(wildcard ./src/lib/*.h)#./src/lib/jobs.h ./src/lib/mainf.h ./src/lib/files.h ./src/lib/menu.h  #$(wildcard ./src/lib/*.h)

OBJ = src/obj/$(subst .c,.o,$(PROJ_MAIN_File)) $(subst .c,.o,$(subst func,obj,$(C_SOURCE)))

executable = $(subst .exe,,$(if exist,$(wildcard $(PROJ_NAME).exe)))

CC = gcc

CC_FLAGS = -c         \
           -W         \
           -Wall      \
           -pedantic

RM  =  del /Q /S *.o *~ *.exe

all: objFolder $(PROJ_NAME) 

$(PROJ_NAME): $(OBJ)
	@ echo 'Building program using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./src/obj/%.o: ./src/func/%.c ./src/lib/%.h
	@ echo 'Building program using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./src/obj/main.o: $(PROJ_MAIN_File) $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ if not exist "src/obj" mkdir "src/obj"

clean:
ifeq ($(executable), )
	@ echo 'There are no files that can be deleted inside the project folder'
else	
	@ echo 'Deleting all objects and the executable from the project folder' 
	@ $(RM) $(PROJ_NAME) *~
	@ echo 'Deleting the objects folder from the project folder' 
	@ rmdir /Q /S "src/obj"
endif

run:
	@ cls
ifeq ($(executable), )
	@ echo 'Cannot run the program because there is no executable file'
else
	@ echo 'Running the program: $(PROJ_NAME)'
	@ ./$(PROJ_NAME)
endif

.PHONY: all clean run
