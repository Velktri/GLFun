CC = g++
CFLAGS = -Wall
PROG = MyProg
SRCS = main.cpp Model.cpp Camera.cpp Input.cpp Draw.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lGL -lGLEW -lglut -lGLU
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
