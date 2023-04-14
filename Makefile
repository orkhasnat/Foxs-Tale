# Makefile for Fox's Tale game

# Set compiler options
CC=g++
CFLAGS=-c -I./include -DROLL
LDFLAGS=-L./lib -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -mwindows -DROLL

# Define source files and object files
SOURCES=$(wildcard ./src/*.cpp)
OBJECTS=$(patsubst ./src/%.cpp, ./obj/%.o, $(SOURCES))

# Define executable name
EXECUTABLE=FoxsTale

# Define cleaning targets
CLEAN_TARGETS=clean cleanall

# Define help message
HELP_MESSAGE=\
	"Available targets:\n"\
	"compile - Compile the game.\n"\
	"clean   - Delete all object files.\n"\
	"cleanall- Delete all object files and the executable.\n"\
	"desktop - Create a desktop shortcut to the executable.\n"\
	"help    - Display this help message.\n"

# Define targets
.PHONY: all
all: compile

.PHONY: compile
compile: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@
	mv $(EXECUTABLE) ./bin/

./obj/%.o: ./src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f ./obj/*.o

.PHONY: cleanall
cleanall: clean
	rm -f ./bin/$(EXECUTABLE)

.PHONY: desktop
desktop:
	@echo "[Desktop Entry]" > FoxsTale.desktop
	@echo "Type=Application" >> FoxsTale.desktop
	@echo "Name=Fox's Tale" >> FoxsTale.desktop
	@echo "Icon=$(PWD)/icon.png" >> FoxsTale.desktop
	@echo "Exec=$(PWD)/bin/$(EXECUTABLE)" >> FoxsTale.desktop
	@echo "Categories=Game" >> FoxsTale.desktop
	@chmod +x FoxsTale.desktop
	@mv FoxsTale.desktop ~/Desktop/

.PHONY: help
help:
	@echo $(HELP_MESSAGE)
