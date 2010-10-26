CXX=g++
#CPPFLAGS=-c -O -g -pg -W -Wall -pedantic
CPPFLAGS=-c -O3 -W -Wall -pedantic
LDFLAGS=-lstdc++

all: debruijn forms inst shitgrep 

debruijn: debruijn.o

forms: forms.o

inst: inst.o

shitgrep: shitgrep.o

clean:
	+rm -f *.o

