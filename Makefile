# Include/ dir and obj/ dir
IDIR=src
ODIR=obj

# Compiler options and flags
CXX=c++

# Check if make is being ran on Windows or Unix
ifeq ($(OS),Windows_NT)
	CXXFLAGS=-I$(IDIR) -Iinclude/ -Llib/
	ERRFLAGS=-Wall -Wunused-variable -Wextra
	OUT_EXT=exe
else
	CXXFLAGS=-I$(IDIR)
	ERRFLAGS=-Wall -Wunused-variable -Wextra
	OUT_EXT=out
endif

# Put header files here
_DEPS=drawable.cpp main.cpp
DEPS=$(patsubst %, $(IDIR)/%, $(_DEPS))

# Put cpp files but change extension to .o
_OBJ=drawable.o main.o
OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))

# Libraries
ifeq ($(OS),Windows_NT)
	LIBS=-lraylib -lopengl32 -lgdi32 -lwinmm
else
	LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Compile .cpp files to .o files
$(ODIR)/%.o: src/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(ERRFLAGS)

# Link .o files and make an executable in bin/ folder
main: $(OBJ)
	$(CXX) -o bin/$@.$(OUT_EXT) $^ $(CXXFLAGS) $(ERRFLAGS) $(LIBS)
	bin/$@.$(OUT_EXT)