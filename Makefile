.SUFFIXES:

include Makefile.conf

#
# Determine the OS we are targeting
#
UNAME_S=$(strip $(shell uname -s))
ifeq ($(UNAME_S),Linux)
IS_LINUX=1
BINEXT=
SHARED_LIB_EXT=.so
STATIC_LIB_EXT=.a
else ifeq ($(UNAME_S:MINGW%=MINGW),MINGW)
IS_WINDOWS=1
BINEXT=.exe
SHARED_LIB_EXT=.so
STATIC_LIB_EXT=.lib
else ifeq ($(UNAME_S),Darwin)
IS_MACOSX=1
BINEXT=
SHARED_LIB_EXT=.dylib
STATIC_LIB_EXT=.a
endif

override CXXFLAGS+=-std=c++0x -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe

INCLUDES=$(addprefix -isystem ,$(sort $(BOOST_INCDIR) $(ICU_INCDIR) $(SCOPE_INCDIR))) -Iinclude

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
LIB_SHARED_LDFLAGS=-shared -fPIC -L$(ICU_LIBDIR) $(LDFLAGS)
LIB_SHARED_LDLIBS=-licuuc -licudata $(LDLIBS)
LIB_SHARED=bin/src/lib/liblightgrep$(SHARED_LIB_EXT)
LIB_STATIC=bin/src/lib/liblightgrep$(STATIC_LIB_EXT)

#
# Setup for test
#
TEST_SRCS=$(wildcard test/*.cpp)
TEST_OBJS=$(TEST_SRCS:%.cpp=bin/%.o)
TEST_SHARED_LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib)) $(LDFLAGS)
TEST_SHARED_LDLIBS=-llightgrep -lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -lboost_system$(BOOST_TYPE) -licuuc -licudata $(LDLIBS)
ifdef IS_LINUX
TEST_SHARED_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
TEST_SHARED_LDLIBS+=-lws2_32 -lmswsock
endif

TEST_STATIC_LDFLAGS=-static-libstdc++ -static-libgcc -static $(TEST_SHARED_LDFLAGS)
TEST_STATIC_LDLIBS=$(TEST_SHARED_LDLIBS) -ldl

TEST_SHARED_BIN=bin/test/test_shared$(BINEXT)
TEST_STATIC_BIN=bin/test/test_static$(BINEXT)

#
# Setup for enc
#
ENC_SRCS=$(wildcard src/enc/*.cpp)
ENC_OBJS=$(ENC_SRCS:%.cpp=bin/%.o)
ENC_SHARED_LDFLAGS=-L$(ICU_LIBDIR) $(LDFLAGS)
ENC_SHARED_LDLIBS=-licuuc -licudata $(LDLIBS)
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
VAL_SHARED_LDFLAGS=-L$(ICU_LIBDIR) -Lbin/src/lib $(LDFLAGS)
VAL_SHARED_LDLIBS=-llightgrep -licuuc -licudata $(LDLIBS)
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
CEX_SHARED_LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib)) $(LDFLAGS)
CEX_SHARED_LDLIBS=-licuuc -licudata -llightgrep $(LDLIBS)
CEX_STATIC_LDFLAGS=-static -static-libstdc++ -static-libgcc $(CEX_SHARED_LDFLAGS)
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

$(CEX_SHARED_BIN): $(CEX_OBJS) $(LIB_SHARED)
	$(CC) -o $@ $(CEX_OBJS) $(CEX_SHARED_LDFLAGS) $(CEX_SHARED_LDLIBS)

ifdef IS_WINDOWS
$(CEX_STATIC_BIN): override CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif
$(CEX_STATIC_BIN): $(CEX_OBJS) $(LIB_STATIC)
	$(CC) -o $@ $(CEX_OBJS) $(CEX_STATIC_LDFLAGS) $(CEX_STATIC_LDLIBS)

$(ENC_SHARED_BIN): $(ENC_OBJS)
	$(CXX) -o $@ $^ $(ENC_SHARED_LDFLAGS) $(ENC_SHARED_LDLIBS)

$(ENC_STATIC_BIN): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(ENC_STATIC_BIN): $(ENC_OBJS)
	$(CXX) -o $@ $^ $(ENC_STATIC_LDFLAGS) $(ENC_STATIC_LDLIBS)

ifndef IS_WINDOWS
$(LIB_SHARED): override CXXFLAGS+=-fPIC
endif
$(LIB_SHARED): $(LIB_SHARED_OBJS)
	$(CXX) -o $@ -shared -fPIC $^ $(LIB_SHARED_LDFLAGS) $(LIB_SHARED_LDLIBS)

$(LIB_STATIC): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(LIB_STATIC): $(LIB_STATIC_OBJS)
	$(AR) rc $@ $^
	$(RANLIB) $@

ifdef IS_WINDOWS
$(TEST_SHARED_BIN): override CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#ifdef IS_WINDOWS_XP
#CPPFLAGS+=-D_WIN32_WINNT=0x0501
#endif
endif
$(TEST_SHARED_BIN): override INCLUDES+=-Itest
$(TEST_SHARED_BIN): $(TEST_OBJS) $(LIB_SHARED)
	$(CXX) -o $@ $(TEST_OBJS) $(TEST_SHARED_LDFLAGS) $(TEST_SHARED_LDLIBS)

$(TEST_STATIC_BIN): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(TEST_STATIC_BIN): override INCLUDES+=-Itest
ifdef IS_WINDOWS
$(TEST_STATIC_BIN): override CPPFLAGS+=-DBOOST_THREAD_USE_LIB
$(TEST_STATIC_BIN): override CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#ifdef IS_WINDOWS_XP
#CPPFLAGS+=-D_WIN32_WINNT=0x0501
#endif
endif
$(TEST_STATIC_BIN): $(TEST_OBJS) $(LIB_STATIC)
	$(CXX) -o $@ $(TEST_OBJS) $(TEST_STATIC_LDFLAGS) $(TEST_STATIC_LDLIBS)

$(VAL_SHARED_BIN): $(VAL_OBJS) $(LIB_SHARED)
	$(CXX) -o $@ $(VAL_OBJS) $(VAL_SHARED_LDFLAGS) $(VAL_SHARED_LDLIBS)

$(VAL_STATIC_BIN): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(VAL_STATIC_BIN): $(VAL_OBJS) $(LIB_STATIC)
	$(CXX) -o $@ $(VAL_OBJS) $(VAL_STATIC_LDFLAGS) $(VAL_STATIC_LDLIBS)

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
