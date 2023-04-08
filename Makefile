homeDir := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
srcDir := $(homeDir)/src
includeDir := $(homeDir)/include
libDir := $(homeDir)/lib
binDir := $(homeDir)/bin

CXX := g++
CXXFLAGS := -I$(includeDir)

LD := g++
linkers := $(shell cat $(homeDir)/linkers.txt)
LDFLAGS := -L$(libDir) $(foreach linker,$(linkers),-l$(linker))

TARGET := Play
SOURCES := $(wildcard $(srcDir)/*.cpp)
OBJECTS := $(patsubst $(srcDir)/%.cpp,$(binDir)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

.PHONY: clean compile

compile:
    @echo "Compiling..."
    @mkdir -p $(binDir)
    @$(MAKE) $(OBJECTS)
    @$(MAKE) $(binDir)/$(TARGET)
    @echo "Done!"

$(binDir)/%.o: $(srcDir)/%.cpp
    $(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(binDir)/$(TARGET): $(OBJECTS)
    @echo "Linking..."
    $(LD) $(LDFLAGS) $^ -o $@
    @echo "Executable generated successfully!"

clean:
    @echo "Cleaning up..."
    @$(RM) $(OBJECTS) $(DEPS) $(binDir)/$(TARGET)
    @echo "Done!"

-include $(DEPS)

shortcut:
    @echo "Creating shortcut..."
    shortcutPath="$(HOME)/Desktop/Play.desktop"
    targetPath="$(binDir)/Play"
    @echo -e "[Desktop Entry]\nType=Application\nName=Play\nExec=$$targetPath\nPath=$(binDir)\nTerminal=false" > "$$shortcutPath"
    @chmod +x "$$shortcutPath"
    @echo "Shortcut created successfully!"