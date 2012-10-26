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
BOOST_INCDIR=../vendors/boost_1_51_0
BOOST_LIBDIR=../vendors/lib
BOOST_TYPE=

ICU_INCDIR=../vendors/icu/include
ICU_LIBDIR=../vendors/lib

SCOPE_INCDIR=../vendors/scope

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

ifndef IS_MACOSX
BUILD_STATIC=1
endif

ifndef IS_WINDOWS
BUILD_SHARED=1
endif

ifdef IS_WINDOWS
CXXFLAGS+=-mthreads
CFLAGS+=-mthreads
LDFLAGS+=-mthreads
endif

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
TEST_SHARED_LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib))
TEST_SHARED_LDLIBS=-llightgrep -lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -lboost_system$(BOOST_TYPE) -licuuc -licudata
ifdef IS_LINUX
TEST_SHARED_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
TEST_SHARED_LDLIBS+=-lws2_32 -lmswsock
endif

TEST_STATIC_LDFLAGS=-static $(TEST_SHARED_LDFLAGS)
TEST_STATIC_LDLIBS=$(TEST_SHARED_LDLIBS) -ldl

TEST_SHARED_BIN=bin/test/test_shared$(BINEXT)
TEST_STATIC_BIN=bin/test/test_static$(BINEXT)

#
# Setup for enc
#
ENC_SRCS=$(wildcard src/enc/*.cpp)
ENC_OBJS=$(ENC_SRCS:%.cpp=bin/%.o)
ENC_SHARED_LDFLAGS=-L$(ICU_LIBDIR)
ENC_SHARED_LDLIBS=-licuuc -licudata
ENC_STATIC_LDFLAGS+=-static $(ENC_SHARED_LDFLAGS)
ENC_STATIC_LDLIBS=$(ENC_SHARED_LDLIBS) -ldl
ifdef IS_LINUX
ENC_STATIC_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
ENC_STATIC_LDLIBS+=-lws2_32 -lmswsock
endif

ENC_SHARED_BIN=bin/src/enc/encodings_shared$(BINEXT)
ENC_STATIC_BIN=bin/src/enc/encodings_static$(BINEXT)

#
# Setup for val
#
VAL_SRCS=$(wildcard src/val/*.cpp)
VAL_OBJS=$(VAL_SRCS:%.cpp=bin/%.o)
VAL_SHARED_LDFLAGS=-L$(ICU_LIBDIR) -Lbin/src/lib
VAL_SHARED_LDLIBS=-llightgrep -licuuc -licudata
VAL_STATIC_LDFLAGS=-static $(VAL_SHARED_LDFLAGS)
VAL_STATIC_LDLIBS=$(VAL_SHARED_LDLIBS) -ldl
ifdef IS_LINUX
VAL_STATIC_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
VAL_STATIC_LDLIBS+=-lws2_32 -lmswsock
endif

VAL_SHARED_BIN=bin/src/val/valid_shared$(BINEXT)
VAL_STATIC_BIN=bin/src/val/valid_static$(BINEXT)

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

ifdef BUILD_SHARED
ALL+=shared
endif

ifdef BUILD_STATIC
ALL+=static
endif

all: $(ALL)

shared: cex-shared enc-shared lib-shared test-shared val-shared

static: cex-static enc-static lib-static test-static val-static

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

cex-shared: $(CEX_SHARED_BIN)

cex-static: $(CEX_STATIC_BIN)

enc-shared: $(ENC_SHARED_BIN)

enc-static: $(ENC_STATIC_BIN)

lib-shared: $(LIB_SHARED)

lib-static: $(LIB_STATIC)

test-shared: $(TEST_SHARED_BIN)
	LD_LIBRARY_PATH=$(BOOST_LIBDIR):$(ICU_LIBDIR):bin/src/lib $< --test

test-static: $(TEST_STATIC_BIN)
	$< --test

val-shared: $(VAL_SHARED_BIN)

val-static: $(VAL_STATIC_BIN)

DEPS=$(patsubst %.o,%.d,$(CEX_OBJS) $(ENC_OBJS) $(LIB_STATIC_OBJS) $(TEST_OBJS) $(VAL_OBJS)) $(LIB_SHARED_OBJS:%.os=%.d)

-include $(DEPS)

$(CEX_SHARED_BIN): LDFLAGS+=$(CEX_LDFLAGS)
$(CEX_SHARED_BIN): LDLIBS+=$(CEX_SHARED_LDLIBS)
$(CEX_SHARED_BIN): $(CEX_OBJS) $(LIB_SHARED)
	$(CC) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

$(CEX_STATIC_BIN): LDFLAGS+=-static $(CEX_LDFLAGS)
ifdef IS_WINDOWS
$(CEX_STATIC_BIN): LDFLAGS+=-static-libstdc++ -static-libgcc
$(CEX_STATIC_BIN): CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif
$(CEX_STATIC_BIN): LDLIBS=$(CEX_STATIC_LDLIBS)
$(CEX_STATIC_BIN): $(CEX_OBJS) $(LIB_STATIC)
	$(CC) -o $@ $(filter-out %.a,$^) $(LDFLAGS) $(LDLIBS)

$(ENC_SHARED_BIN): LDFLAGS+=$(ENC_SHARED_LDFLAGS)
$(ENC_SHARED_BIN): LDLIBS=$(ENC_SHARED_LDLIBS)
$(ENC_SHARED_BIN): $(ENC_OBJS)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

$(ENC_STATIC_BIN): CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(ENC_STATIC_BIN): LDFLAGS+=$(ENC_STATIC_LDFLAGS)
$(ENC_STATIC_BIN): LDLIBS=$(ENC_STATIC_LDLIBS)
$(ENC_STATIC_BIN): $(ENC_OBJS)
	$(CXX) -o $@ $(filter-out %.a,$^) $(LDFLAGS) $(LDLIBS)

ifndef IS_WINDOWS
$(LIB_SHARED): CXXFLAGS+=-fPIC
endif
$(LIB_SHARED): LDFLAGS+=$(LIB_SHARED_LDFLAGS)
$(LIB_SHARED): LDLIBS=$(LIB_SHARED_LDLIBS)
$(LIB_SHARED): $(LIB_SHARED_OBJS)
	$(CXX) -o $@ -shared $^ $(LDFLAGS) $(LDLIBS)

$(LIB_STATIC): CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(LIB_STATIC): $(LIB_STATIC_OBJS)
	$(AR) rc $@ $^
	$(RANLIB) $@

ifdef IS_WINDOWS
$(TEST_SHARED_BIN): CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#ifdef IS_WINDOWS_XP
#CPPFLAGS+=-D_WIN32_WINNT=0x0501
#endif
endif
$(TEST_SHARED_BIN): INCLUDES+=-Itest
$(TEST_SHARED_BIN): LDFLAGS+=$(TEST_SHARED_LDFLAGS)
$(TEST_SHARED_BIN): LDLIBS=$(TEST_SHARED_LDLIBS)
$(TEST_SHARED_BIN): $(TEST_OBJS) $(LIB_SHARED)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

$(TEST_STATIC_BIN): CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(TEST_STATIC_BIN): INCLUDES+=-Itest
$(TEST_STATIC_BIN): LDFLAGS+=$(TEST_STATIC_LDFLAGS)
$(TEST_STATIC_BIN): LDLIBS=$(TEST_STATIC_LDLIBS)
ifdef IS_WINDOWS
$(TEST_STATIC_BIN): LDFLAGS+=-static-libstdc++ -static-libgcc
$(TEST_STATIC_BIN): CPPFLAGS+=-DBOOST_THREAD_USE_LIB
$(TEST_STATIC_BIN): CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#ifdef IS_WINDOWS_XP
#CPPFLAGS+=-D_WIN32_WINNT=0x0501
#endif
endif
$(TEST_STATIC_BIN): $(TEST_OBJS) $(LIB_STATIC)
	$(CXX) -o $@ $(filter-out %.a,$^) $(LDFLAGS) $(LDLIBS)

$(VAL_SHARED_BIN): LDFLAGS+=$(VAL_SHARED_LDFLAGS)
$(VAL_SHARED_BIN): LDLIBS=$(VAL_SHARED_LDLIBS)
$(VAL_SHARED_BIN): $(VAL_OBJS) $(LIB_SHARED)
	$(CXX) -o $@ $(filter-out %.so,$^) $(LDFLAGS) $(LDLIBS)

$(VAL_STATIC_BIN): CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(VAL_STATIC_BIN): LDFLAGS+=$(VAL_STATIC_LDFLAGS)
$(VAL_STATIC_BIN): LDLIBS=$(VAL_STATIC_LDLIBS)
$(VAL_STATIC_BIN): $(VAL_OBJS) $(LIB_STATIC)
	$(CXX) -o $@ $(filter-out %.a,$^) $(LDFLAGS) $(LDLIBS)

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

.PRECIOUS: bin/%.tab.cpp

%.tab.os: %.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<

%.tab.o: %.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<
