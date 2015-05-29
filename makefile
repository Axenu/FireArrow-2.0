# Object files to either reference or create
SOURCES=main.cpp FANode.cpp FARenderPass.cpp FAScene.cpp FAModel.cpp FAMaterial.cpp FAMaterialComponent.cpp FAMesh.cpp FACamera.cpp FAShader.cpp
# The executable file that will be created
EXEC = main
# The c++ flags to use for compilation
CXXFLAGS = -Wall
# The c++ compiler to use for compilation
CC = clang++

SDIR=src
ODIR=build
OBJECTS = $(addprefix $(ODIR)/, $(SOURCES:.cpp=.o))
lIBDIR=lib/
IDIR=include/


# This section is called on 'make'
# Will call compile, and then call clean
all: $(OBJECTS)
	$(CC) -L $(lIBDIR) -std=c++11 -o $(EXEC) $^ -framework IOKit -framework Cocoa -framework OpenGL -framework CoreVideo -lglfw3

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -I $(IDIR) -std=c++11 -Wno-c++11-long-long -Wall -c -o $@ $<

clean:
	rm -f $(ODIR)/*.o