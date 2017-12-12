CCFLAGS=-c -O2 -fPIC
CXXFLAGS= -std=gnu++11

# build Omega2HCSR04 executable when user executes "make"
SOURCES=$(shell find -name "*.cpp" | sed s:./:: | tr "\n" " ")
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

# Includes and libraries
INC=-I ./header

# Main build target
TARGET=Omega2HCSR04

# Default target - build everything
all: precomp $(TARGET)

# Link target
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

# Compile sources
build/%.o: ./source/%.cpp
	$(CXX) $(CXXFLAGS) $(CCFLAGS) $(INC) $< -o $@

# Remove all created files
clean:
	rm -rf build/*
	rm -rf dist/*

# Ensure required sub-directories are created
precomp:
	@mkdir -p build
	@mkdir -p dist