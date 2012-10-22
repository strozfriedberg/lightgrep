.SUFFIXES:

#
# Directory configuration
#
BINDIR=bin
INCDIR=include
SRCDIR=src

#
# Setup for liblightgrep
#
LIB_SRCS=$(wildcard src/lib/*.cpp) 
LIB_SHARED_OBJS=$(LIB_SRCS:%.cpp=bin/%.os) bin/src/lib/parser.tab.os
LIB_STATIC_OBJS=$(LIB_SRCS:%.cpp=bin/%.o) bin/src/lib/parser.tab.o

#
# Setup for test
#
TEST_SRCS=$(wildcard test/*.cpp)
TEST_OBJS=$(TEST_SRCS:%.cpp=bin/%.o)
TEST_LDFLAGS=$(foreach dir,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib),-L$(dir))
TEST_LDLIBS=-lboost_system$(BOOST_TYPE) -lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -llightgrep -licuuc -licudata -lpthread

#
# Setup for enc
#
ENC_SRCS=$(wildcard src/enc/*.cpp)
ENC_OBJS=$(ENC_SRCS:%.cpp=bin/%.o)
ENC_LDFLAGS=-L$(ICU_LIBDIR)
ENC_LDLIBS=-licuuc -licudata

#
# Setup for val
#
VAL_SRCS=$(wildcard src/val/*.cpp)
VAL_OBJS=$(VAL_SRCS:%.cpp=bin/%.o)
VAL_LDFLAGS=-L$(ICU_LIBDIR) -Lbin/src/lib
VAL_LDLIBS=-licuuc -licudata -llightgrep

#
# Setup for c_example
#
CEX_SRCS=$(wildcard c_example/*.c)
CEX_OBJS=$(CEX_SRCS:%.c=bin/%.o)
CEX_LDFLAGS=-L$(ICU_LIBDIR) -Lbin/src/lib
CEX_LDLIBS=-licuuc -licudata -llightgrep

#
# External library configuration
#
BOOST_INCDIR=vendors/boost
BOOST_LIBDIR=lib
BOOST_TYPE=

ICU_INCDIR=vendors/icu/include
ICU_LIBDIR=lib

SCOPE_INCDIR=vendors/scope

#
# C/C++ compilation and linking
#
CC=gcc
CXX=g++
CPPFLAGS=-MMD -MP
CFLAGS=-std=c1x -O3 -W -Wall -Wextra -pedantic -pipe
CXXFLAGS=-std=c++0x -O3 -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe
INCLUDES=$(foreach dir,$(sort $(BOOST_INCDIR) $(ICU_INCDIR) $(SCOPE_INCDIR)),-isystem $(dir)) -I$(INCDIR)
LDFLAGS=
LDLIBS=

DEPS=$(patsubst %.o,%.d,$(CEX_OBJS) $(ENC_OBJS) $(LIB_STATIC_OBJS) $(TEST_OBJS) $(VAL_OBJS)) $(LIB_SHARED_OBJS:%.os=%.d)

#
# Other programs
#
BISON=bison
RANLIB=ranlib
MKDIR=mkdir

#
# Goals
#
all: cex enc shared-lib static-lib test val

cex: bin/c_example/c_example

enc: bin/src/enc/encodings

shared-lib: bin/src/lib/liblightgrep.so

static-lib: bin/src/lib/liblightgrep.a

test: bin/test/test
	LD_LIBRARY_PATH=lib:bin/src/lib $< --test

val: bin/src/val/valid

-include $(DEPS)

bin/c_example/c_example: LDFLAGS=$(CEX_LDFLAGS)
bin/c_example/c_example: LDLIBS=$(CEX_LDLIBS)
bin/c_example/c_example: $(CEX_OBJS) bin/src/lib/liblightgrep.so
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

bin/src/enc/encodings: LDFLAGS=$(ENC_LDFLAGS)
bin/src/enc/encodings: LDLIBS=$(ENC_LDLIBS)
bin/src/enc/encodings: $(ENC_OBJS)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

bin/src/lib/liblightgrep.so: $(LIB_SHARED_OBJS)
	$(CXX) -o $@ -shared $^

bin/src/lib/liblightgrep.a: $(LIB_STATIC_OBJS)
	$(AR) rc $@ $^
	$(RANLIB) $@

bin/test/test: INCLUDES+=-Itest
bin/test/test: LDFLAGS=$(TEST_LDFLAGS)
bin/test/test: LDLIBS=$(TEST_LDLIBS)
bin/test/test: $(TEST_OBJS) bin/src/lib/liblightgrep.so
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

bin/src/val/valid: LDFLAGS=$(VAL_LDFLAGS)
bin/src/val/valid: LDLIBS=$(VAL_LDLIBS)
bin/src/val/valid: $(VAL_OBJS) bin/src/lib/liblightgrep.so
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

bin/c_example bin/src/enc bin/src/lib bin/src/val bin/test:
	$(MKDIR) -p $@

clean:
	$(RM) -r $(BINDIR)/*

.PHONY: all cex clean enc shared-lib static-lib test val

#
# Patterns
#
.SECONDEXPANSION:
bin/%.o: %.c | $$(@D)
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $(INCLUDES) $<

.SECONDEXPANSION:
bin/%.os: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) -fPIC $(INCLUDES) $<

.SECONDEXPANSION:
bin/%.o: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<

.SECONDEXPANSION:
bin/%.tab.cpp: %.ypp | $$(@D)
	$(BISON) -r solved $< -o $@

.PRECIOUS: %.tab.cpp

%.tab.os: %.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) -fPIC $(INCLUDES) $<

%.tab.o: %.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<
