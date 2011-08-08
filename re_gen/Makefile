CXX=g++
#CPPFLAGS=-c -O -g -pg -W -Wall -pedantic
CPPFLAGS=-c -O3 -W -Wall -pedantic
LDFLAGS=-lstdc++ -lpcre

all: debruijn forms inst randpat shitgrep 

debruijn: debruijn.o

forms: forms.o

inst: inst.o

randpat: randpat.o unparser.o node.o

shitgrep: shitgrep.o

clean:
	+rm -f *.o debruijn forms inst shitgrep

