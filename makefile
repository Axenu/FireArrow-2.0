# Object files to either reference or create
SOURCES=main.cpp FANode.cpp FARenderPass.cpp FAScene.cpp
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
	$(CC) -L $(lIBDIR) -o $(EXEC) $^ -framework IOKit -framework Cocoa -framework OpenGL -framework CoreVideo -lglfw3

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(CC) -I $(IDIR) -Wc++11-extensions -c -o $@ $<

clean:
	rm -f $(ODIR)/*.o