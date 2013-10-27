CC=g++
CXX=g++
#CPPFLAGS=-c -O -g -pg -W -Wall -pedantic
CPPFLAGS=-c -O3 -W -Wall -pedantic -std=c++11
LDFLAGS=-L/usr/lib/x86_64-linux-gnu -L/lib/x86_64-linux-gnu -lstdc++ -lpcre

all: randpat shitgrep

randpat: randpat.o unparser.o node.o

shitgrep: shitgrep.o

clean:
	+rm -f *.o randpat shitgrep

