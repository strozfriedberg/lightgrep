.SUFFIXES:

#
# Determine the OS we are targeting
#
UNAME_S=$(strip $(shell uname -s))
ifeq ($(UNAME_S),Linux)
IS_LINUX=1
BINEXT=
else ifeq ($(UNAME_S:MINGW%=MINGW),MINGW)
IS_WINDOWS=1
BINEXT=.exe
else ifeq ($(UNAME_S),Darwin)
IS_MACOSX=1
BINEXT=
endif

#
# External library configuration
#
BOOST_INCDIR=../lg-libs/boost_1_51_0
BOOST_LIBDIR=../lg-libs/lib
BOOST_TYPE=

ICU_INCDIR=../lg-libs/icu/include
ICU_LIBDIR=../lg-libs/lib

SCOPE_INCDIR=../lg-libs/scope

#
# C/C++ compilation and linking
#
CC=gcc
CXX=g++
CPPFLAGS=-MMD -MP
CFLAGS=-std=c1x -O3 -W -Wall -Wextra -pedantic -pipe
CXXFLAGS=-std=c++0x -O3 -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe
INCLUDES=$(addprefix -isystem ,$(sort $(BOOST_INCDIR) $(ICU_INCDIR) $(SCOPE_INCDIR))) -Iinclude
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
LIB_SHARED_LDFLAGS=-L$(ICU_LIBDIR)
LIB_SHARED_LDLIBS=-licuuc -licudata
LIB_SHARED=bin/src/lib/liblightgrep.so
LIB_STATIC=bin/src/lib/liblightgrep.a

#
# Setup for test
#
TEST_SRCS=$(wildcard test/*.cpp)
TEST_OBJS=$(TEST_SRCS:%.cpp=bin/%.o)
TEST_LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib))
TEST_LDLIBS=-llightgrep -lboost_system$(BOOST_TYPE) -lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -licuuc -licudata
ifdef IS_LINUX
TEST_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
TEST_LDLIBS+=-lws2_32 -lmswsock
endif
TEST_BIN=bin/test/test$(BINEXT)

#
# Setup for enc
#
ENC_SRCS=$(wildcard src/enc/*.cpp)
ENC_OBJS=$(ENC_SRCS:%.cpp=bin/%.o)
ENC_LDFLAGS=-L$(ICU_LIBDIR)
ENC_LDLIBS=-licuuc -licudata
ENC_BIN=bin/src/enc/encodings$(BINEXT)

#
# Setup for val
#
VAL_SRCS=$(wildcard src/val/*.cpp)
VAL_OBJS=$(VAL_SRCS:%.cpp=bin/%.o)
VAL_LDFLAGS=-L$(ICU_LIBDIR) -Lbin/src/lib
VAL_LDLIBS=-licuuc -licudata -llightgrep
VAL_BIN=bin/src/val/valid$(BINEXT)

#
# Setup for c_example
#
CEX_SRCS=$(wildcard c_example/*.c)
CEX_OBJS=$(CEX_SRCS:%.c=bin/%.o)
CEX_LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib))
CEX_SHARED_LDLIBS=-licuuc -licudata -llightgrep
CEX_STATIC_LDLIBS=-llightgrep -licuuc -licudata -lstdc++ -ldl -lm
ifdef IS_LINUX
CEX_STATIC_LDLIBS+=-lpthread
endif
CEX_SHARED_BIN=bin/c_example/main_shared$(BINEXT)
CEX_STATIC_BIN=bin/c_example/main_static$(BINEXT)

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

cex: $(CEX_SHARED_BIN) $(CEX_STATIC_BIN)

enc: $(ENC_BIN)

shared-lib: $(LIB_SHARED)

static-lib: $(LIB_STATIC)

test: $(TEST_BIN)
	LD_LIBRARY_PATH=lib:bin/src/lib $< --test

val: $(VAL_BIN)

-include $(DEPS)

$(CEX_SHARED_BIN): LDFLAGS=$(CEX_LDFLAGS)
$(CEX_SHARED_BIN): LDLIBS=$(CEX_SHARED_LDLIBS)
$(CEX_SHARED_BIN): $(CEX_OBJS) $(LIB_SHARED)
	$(CC) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

$(CEX_STATIC_BIN): LDFLAGS=-static $(CEX_LDFLAGS)
ifdef IS_WINDOWS
$(CEX_STATIC_BIN): LDFLAGS+=-static-libstdc++ -static-libgcc
$(CEX_STATIC_BIN): CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif
$(CEX_STATIC_BIN): LDLIBS=$(CEX_STATIC_LDLIBS)
$(CEX_STATIC_BIN): $(CEX_OBJS) $(LIB_STATIC)
	$(CC) -o $@ $(filter-out %.a,$^) $(LDFLAGS) $(LDLIBS)

$(ENC_BIN): LDFLAGS=$(ENC_LDFLAGS)
$(ENC_BIN): LDLIBS=$(ENC_LDLIBS)
$(ENC_BIN): $(ENC_OBJS)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

ifndef IS_WINDOWS
$(LIB_SHARED): CXXFLAGS+=-fPIC
endif
$(LIB_SHARED): LDFLAGS=$(LIB_SHARED_LDFLAGS)
$(LIB_SHARED): LDLIBS=$(LIB_SHARED_LDLIBS)
$(LIB_SHARED): $(LIB_SHARED_OBJS)
	$(CXX) -o $@ -shared $^ $(LDFLAGS) $(LDLIBS)

$(LIB_STATIC): $(LIB_STATIC_OBJS)
	$(AR) rc $@ $^
	$(RANLIB) $@

$(TEST_BIN): INCLUDES+=-Itest
$(TEST_BIN): LDFLAGS=$(TEST_LDFLAGS)
$(TEST_BIN): LDLIBS=$(TEST_LDLIBS)
$(TEST_BIN): $(TEST_OBJS) $(LIB_SHARED)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

$(VAL_BIN): LDFLAGS=$(VAL_LDFLAGS)
$(VAL_BIN): LDLIBS=$(VAL_LDLIBS)
$(VAL_BIN): $(VAL_OBJS) $(LIB_SHARED)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

bin/c_example bin/src/enc bin/src/lib bin/src/val bin/test:
	$(MKDIR) -p $@

clean:
	$(RM) -r bin/*

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
