CC = gcc
CFLAGS = -g -pedantic -Wall -Wextra -Werror -fdiagnostics-color=always

MAIN_FILE = main.c
SELECTION_FILES = src/selection.h src/selection.c
SELECTION_ERROR_MANAGEMENT_FILES = src/selection_error_management.h src/selection_error_management.c
RESOURCE_FILES = src/resources/resource.rc src/resources/resource.h

OBJECTS = main.o selection.o selection_error_management.o resource.res

SEPARATOR = @echo -----------------
.PHONY = clean_obj clean_all build_clean

build_clean: build clean_obj

clean_all: clean_obj
	-del -fR *.exe
	@echo [INFO]: file eseguibile eliminato
	$(SEPARATOR)

clean_obj:
	-del -fR *.o 
	-del -fR *.res
	-del -fR src\*.h.gch
	@echo [INFO]: file oggetto eliminati
	$(SEPARATOR)

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o Option-Selector.exe
	@echo [INFO]: file eseguibile creato con successo
	$(SEPARATOR)

main.o: $(MAIN_FILE)
	$(CC) $(CFLAGS) -c $(MAIN_FILE)
	@echo [INFO]: compilato: $(MAIN_FILE)
	$(SEPARATOR)

selection.o: $(SELECTION_FILES)
	$(CC) $(CFLAGS) -c $(SELECTION_FILES)
	@echo [INFO]: compilati: $(SELECTION_FILES)
	$(SEPARATOR)

selection_error_management.o: $(SELECTION_ERROR_MANAGEMENT_FILES)
	$(CC) $(CFLAGS) -c $(SELECTION_ERROR_MANAGEMENT_FILES)
	@echo [INFO]: compilati: $(SELECTION_ERROR_MANAGEMENT_FILES)
	$(SEPARATOR)

resource.res: $(RESOURCE_FILES)
	windres src/resources/resource.rc -O coff resource.res
	@echo [INFO]: compilati: $(RESOURCE_FILES)
	$(SEPARATOR)