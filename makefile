#les variables
SRC_DIR1 := Projet_Unix_Part1/src
BUILD_DIR1 := Projet_Unix_Part1/build
SRC_DIR := Projet_Unix_Part2/src
BUILD_DIR := Projet_Unix_Part2/build
PROG_NAME=interface

#fichier sources .c, wilcard est equivalent à *.c càd tous les fichiers.c
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
SRC_FILES1 := $(wildcard $(SRC_DIR1)/*.c)

#variable flag pour l'interface et les autres fichiers.c
CFLAGS := -Wall -g
CFLAGS2=`pkg-config --cflags gtk+-3.0` 
LIBS=`pkg-config --libs gtk+-3.0`

#compilateur object 
CC := gcc

# % compiler tous les fichiers .c en des fichiers executables
all: $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) interface $(SRC_FILES1:$(SRC_DIR1)/%.c=$(BUILD_DIR1)/%)  
		
#attribution des droits (read, write et execute pour Owner, group et other)
	chmod 777 $(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%) interface
	chmod 777 $(SRC_FILES1:$(SRC_DIR1)/%.c=$(BUILD_DIR1)/%) interface

interface: interface.c 
	$(CC) ${CFLAGS2} -o ${PROG_NAME} ${PROG_NAME}.c ${LIBS}

#creation d'un dossier build contenant les fichiers executables 
$(BUILD_DIR)/%: $(SRC_DIR)/%.c 
	@mkdir -p $(@D)
	$(CC)  $(CFLAGS) -o $@ $^

$(BUILD_DIR1)/%: $(SRC_DIR1)/%.c 
	@mkdir -p $(@D)
	$(CC)  $(CFLAGS) -o $@ $^ 

#effacer le dossier build 
clean:
	rm -rf Projet_Unix_Part1/build
	rm -rf Projet_Unix_Part2/build
	rm -f interface



	
