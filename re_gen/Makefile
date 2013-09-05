CXX=g++
#CPPFLAGS=-c -O -g -pg -W -Wall -pedantic
CPPFLAGS=-c -O3 -W -Wall -pedantic
LDFLAGS=-lstdc++ -lpcre

all: randpat shitgrep

randpat: randpat.o unparser.o node.o

shitgrep: shitgrep.o

clean:
	+rm -f *.o randpat shitgrep

