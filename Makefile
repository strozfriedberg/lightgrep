.SUFFIXES:

#
# Determine the OS we are targeting
#
UNAME_S=$(strip $(shell uname -s))
ifeq ($(UNAME_S),Linux)
IS_LINUX=1
else ifeq ($(UNAME_S:MINGW%=MINGW),MINGW)
IS_WINDOWS=1
else ifeq ($(UNAME_S),Darwin)
IS_MACOSX=1
endif

#
# Directory configuration
#
BINDIR=bin
INCDIR=include
SRCDIR=src

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

ifdef IS_WINDOWS
CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#ifdef IS_WINDOWS_XP
#CPPFLAGS+=-D_WIN32_WINNT=0x0501
#endif
CXXFLAGS+=-mthreads
endif

DEPS=$(patsubst %.o,%.d,$(CEX_OBJS) $(ENC_OBJS) $(LIB_STATIC_OBJS) $(TEST_OBJS) $(VAL_OBJS)) $(LIB_SHARED_OBJS:%.os=%.d)

#
# Other programs
#
BISON=bison
RANLIB=ranlib
MKDIR=mkdir

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
TEST_LDLIBS=-llightgrep -lboost_system$(BOOST_TYPE) -lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -licuuc -licudata
ifdef IS_LINUX
TEST_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
TEST_LDLIBS+=-lws2_32 -lmswsock
endif

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
CEX_LDFLAGS=$(foreach dir,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib),-L$(dir))
CEX_SHARED_LDLIBS=-licuuc -licudata -llightgrep
CEX_STATIC_LDLIBS=-llightgrep -licuuc -licudata -lstdc++ -ldl -lm
ifdef IS_LINUX
CEX_STATIC_LDLIBS+=-lpthread
endif

#
# Goals
#
all: cex enc shared-lib static-lib test val

debug: CFLAGS+=-g
debug: CFLAGS:=$(filter-out -O3, $(CFLAGS))
debug: CXXFLAGS+=-g
debug: CXXFLAGS:=$(filter-out -O3, $(CXXFLAGS))
ifndef IS_WINDOWS
debug: CXXFLAGS+=-fstack-protector-all
endif 
debug: all

perf: CFLAGS+=-g
perf: CXXFLAGS+=-g
perf: all

cex: bin/c_example/main_shared bin/c_example/main_static

enc: bin/src/enc/encodings

shared-lib: bin/src/lib/liblightgrep.so

static-lib: bin/src/lib/liblightgrep.a

test: bin/test/test
	LD_LIBRARY_PATH=lib:bin/src/lib $< --test

val: bin/src/val/valid

-include $(DEPS)

bin/c_example/main_shared: LDFLAGS=$(CEX_LDFLAGS)
bin/c_example/main_shared: LDLIBS=$(CEX_SHARED_LDLIBS)
bin/c_example/main_shared: $(CEX_OBJS) bin/src/lib/liblightgrep.so
	$(CC) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

bin/c_example/main_static: LDFLAGS=-static $(CEX_LDFLAGS)
ifdef IS_WINDOWS
bin/c_example/main_static: LDFLAGS+=-static-libstdc++ -static-libgcc
endif
bin/c_example/main_static: LDLIBS=$(CEX_STATIC_LDLIBS)
bin/c_example/main_static: $(CEX_OBJS) bin/src/lib/liblightgrep.a
	$(CC) -o $@ $(filter-out %.a,$^) $(LDFLAGS) $(LDLIBS)

bin/src/enc/encodings: LDFLAGS=$(ENC_LDFLAGS)
bin/src/enc/encodings: LDLIBS=$(ENC_LDLIBS)
bin/src/enc/encodings: $(ENC_OBJS)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

bin/src/lib/liblightgrep.so: CXXFLAGS+=-fPIC
bin/src/lib/liblightgrep.so: $(LIB_SHARED_OBJS)
	$(CXX) -o $@ -shared $^

ifdef IS_WINDOWS
bin/src/lib/liblightgrep.a: CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif
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

.PHONY: all cex clean debug enc shared-lib static-lib test val

#
# Patterns
#
.SECONDEXPANSION:
bin/%.o: %.c | $$(@D)
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $(INCLUDES) $<

.SECONDEXPANSION:
bin/%.os: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<

.SECONDEXPANSION:
bin/%.o: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<

.SECONDEXPANSION:
bin/%.tab.cpp: %.ypp | $$(@D)
	$(BISON) -r solved $< -o $@

.PRECIOUS: %.tab.cpp

%.tab.os: %.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<

%.tab.o: %.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<
