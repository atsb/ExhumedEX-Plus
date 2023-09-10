# Compiler and compiler flags
CXX = g++
CXXFLAGS = -g -L ../angelscript/angelscript/lib -I ./framework -I ./game -I ./math -I ./opengl -I ./renderer -I ./script -I ./script/objects -I ./system -I ./system/sdl -I ./system/al -I . -I ../angelscript/angelscript/include -I ./tools/mapEditor -fpermissive
LIBS = -lpng -lvorbis -lvorbisfile -logg -lz -lSDL2 -langelscript -lopenal -lGL

# Source files
SRCS = $(wildcard framework/*.cpp) $(wildcard game/*.cpp) $(wildcard math/*.cpp) $(wildcard opengl/*.cpp) $(wildcard renderer/*.cpp) $(wildcard script/*.cpp) $(wildcard script/objects/*.cpp) $(wildcard system/*.cpp) $(wildcard system/sdl/*.cpp) $(wildcard tools/mapEditor/*.cpp) system/al/soundOAL.cpp main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
EXECUTABLE = exhumed-ex-plus

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJS)

.PHONY: all clean
