# Object files to either reference or create
# SOURCES=main.cpp FANode.cpp FARenderPass.cpp FAEngine.cpp FAScene.cpp FAModel.cpp FAMaterial.cpp FAMaterialComponent.cpp FAMesh.cpp FACamera.cpp FAShader.cpp Game.cpp testScene.cpp FAFont.cpp FAText.cpp FAHUDElement.cpp
SOURCES=$(wildcard src/*.cpp)
SOURCEFILES = $(SOURCES:src/%=%)
# The executable file that will be created
EXEC = main
# The c++ flags to use for compilation
CXXFLAGS = -Wall
# The c++ compiler to use for compilation
CC = clang++

SDIR=src
ODIR=build
OBJECTS = $(addprefix $(ODIR)/, $(SOURCEFILES:.cpp=.o))
lIBDIR=lib/
IDIR=include/

LIB=-lglfw3 -lIL -ltiff -lpng16 -lz -ljasper -ljpeg -llzma -lfreetype -lbz2

#OSX frameworks
FRAMEWORKS=-framework IOKit -framework Cocoa -framework OpenGL -framework CoreVideo


# This section is called on 'make'
# Will call compile, and then call clean
all: $(OBJECTS)
	$(CC) -L $(lIBDIR) -std=c++11 -o $(EXEC) $^ $(FRAMEWORKS) $(LIB)

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -I $(IDIR) -std=c++11 -Wno-c++11-long-long -Wall -c -o $@ $<

clean:
	rm -f $(ODIR)/*.o