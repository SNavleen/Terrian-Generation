LDFLAGS = -lGL -lGLU -lglut
CFLAGS=-g -Wall -std=c++11
CC=g++
EXEEXT=
PROGRAM_NAME= Terrain

# Windows (cygwin)
ifeq "$(OS)" "Windows_NT"
	EXEEXT=.exe #on windows applications must have .exe extension
	RM=del #rm command for windows powershell
    LDFLAGS = -lfreeglut -lglu32 -lopengl32
else
	# OS X
	OS := $(shell uname)
	ifeq ($(OS), Darwin)
	        LDFLAGS = -framework Carbon -framework OpenGL -framework GLUT
	endif
endif

run: $(PROGRAM_NAME) clean

clean:
	rm $(PROGRAM_NAME)$(EXEEXT)
	rm *.o

$(PROGRAM_NAME): Terrain.o Window.o DrawMesh.o Face.o D2Face.o Vertex.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	./$(PROGRAM_NAME)$(EXEEXT)
