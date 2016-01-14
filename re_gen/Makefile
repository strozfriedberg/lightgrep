CC=g++
CXX=g++
CPPFLAGS=-O3 -W -Wall -Wextra -pedantic -std=c++11
LDFLAGS=-lpcre -lstdc++

all: parsecheck randpat shitgrep

parsecheck: parsecheck.o

randpat: randpat.o unparser.o node.o

shitgrep: shitgrep.o

clean:
	+rm -f *.o parsecheck randpat shitgrep

