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
STATIC_LIB_EXT=.a
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
LIB_SHARED_LDFLAGS=-L$(ICU_LIBDIR) $(LDFLAGS)
LIB_SHARED_LDLIBS=-licuuc -licudata $(LDLIBS)
LIB_SHARED=bin/src/lib/liblightgrep$(SHARED_LIB_EXT)
LIB_STATIC=bin/src/lib/liblightgrep$(STATIC_LIB_EXT)

#
# Setup for test
#
TEST_SRCS=$(wildcard test/*.cpp)
TEST_OBJS=$(TEST_SRCS:%.cpp=bin/%.o)
TEST_LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib)) $(LDFLAGS)
TEST_LDLIBS=-llightgrep -lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -lboost_system$(BOOST_TYPE) -licuuc -licudata $(LDLIBS)
ifdef IS_LINUX
TEST_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
TEST_LDLIBS+=-lws2_32 -lmswsock
endif

ifndef BUILD_SHARED
TEST_LDFLAGS+=-static-libstdc++ -static-libgcc -static
TEST_LDLIBS+=-ldl
endif

TEST_BIN=bin/test/test$(BINEXT)

#
# Setup for enc
#
ENC_SRCS=$(wildcard src/enc/*.cpp)
ENC_OBJS=$(ENC_SRCS:%.cpp=bin/%.o)
ENC_LDFLAGS=-L$(ICU_LIBDIR) $(LDFLAGS)
ENC_LDLIBS=-licuuc -licudata $(LDLIBS)

ifndef BUILD_SHARED
ENC_LDFLAGS+=-static-libstdc++ -static-libgcc -static
ENC_LDLIBS+=-ldl
ifdef IS_LINUX
ENC_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
ENC_LDLIBS+=-lws2_32 -lmswsock
endif
endif

ENC_BIN=bin/src/enc/encodings$(BINEXT)

#
# Setup for val
#
VAL_SRCS=$(wildcard src/val/*.cpp)
VAL_OBJS=$(VAL_SRCS:%.cpp=bin/%.o)
VAL_LDFLAGS=-L$(ICU_LIBDIR) -Lbin/src/lib $(LDFLAGS)
VAL_LDLIBS=-llightgrep -licuuc -licudata $(LDLIBS)

ifndef BUILD_SHARED
VAL_LDFLAGS+=-static-libstdc++ -static-libgcc -static
VAL_LDLIBS+=-ldl
ifdef IS_LINUX
VAL_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
VAL_LDLIBS+=-lws2_32 -lmswsock
endif
endif

VAL_BIN=bin/src/val/valid$(BINEXT)

#
# Setup for c_example
#
CEX_SRCS=$(wildcard c_example/*.c)
CEX_OBJS=$(CEX_SRCS:%.c=bin/%.o)
CEX_LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) bin/src/lib)) $(LDFLAGS)
CEX_LDLIBS=-licuuc -licudata -llightgrep $(LDLIBS)

ifndef BUILD_SHARED
CEX_LDFLAGS+=-static-libstdc++ -static-libgcc -static
CEX_LDLIBS+=-ldl -lm
ifdef IS_LINUX
VAL_LDLIBS+=-lpthread
else ifdef IS_WINDOWS
VAL_LDLIBS+=-lws2_32 -lmswsock
endif
endif

CEX_BIN=bin/c_example/main$(BINEXT)

#
# Goals
#

ALL=cex enc test val

ifeq ($(BUILD_SHARED),1)
ALL:=lib-shared $(ALL)
endif

ifeq ($(BUILD_STATIC),1)
ALL:=lib-static $(ALL)
endif

all: $(ALL) 

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

cex: $(CEX_BIN)

enc: $(ENC_BIN)

lib-shared: $(LIB_SHARED)

lib-static: $(LIB_STATIC)

test: $(TEST_BIN)
	LD_LIBRARY_PATH=$(BOOST_LIBDIR):$(ICU_LIBDIR):bin/src/lib $< --test

val: $(VAL_BIN)

DEPS=$(patsubst %.o,%.d,$(CEX_OBJS) $(ENC_OBJS) $(LIB_STATIC_OBJS) $(TEST_OBJS) $(VAL_OBJS)) $(LIB_SHARED_OBJS:%.os=%.d)

-include $(DEPS)


ifndef BUILD_SHARED
$(CEX_BIN): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
ifdef IS_WINDOWS
$(CEX_BIN): override CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif
$(CEX_BIN): $(CEX_OBJS) $(LIB_STATIC)
else
$(CEX_BIN): $(CEX_OBJS) $(LIB_SHARED)
endif
	$(CC) -o $@ $(CEX_OBJS) $(CEX_LDFLAGS) $(CEX_LDLIBS)

ifndef BUILD_SHARED
$(ENC_BIN): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(ENC_BIN): $(ENC_OBJS) $(LIB_STATIC)
else
$(ENC_BIN): $(ENC_OBJS) $(LIB_SHARED)
endif
	$(CXX) -o $@ $^ $(ENC_LDFLAGS) $(ENC_LDLIBS)

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
$(TEST_BIN): override CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
#ifdef IS_WINDOWS_XP
#CPPFLAGS+=-D_WIN32_WINNT=0x0501
#endif
endif
$(TEST_BIN): override INCLUDES+=-Itest
ifndef BUILD_SHARED
$(TEST_BIN): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
ifdef IS_WINDOWS
$(TEST_BIN): override CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif
$(TEST_BIN): $(TEST_OBJS) $(LIB_STATIC)
else
$(TEST_BIN): $(TEST_OBJS) $(LIB_SHARED)
endif
	$(CXX) -o $@ $(TEST_OBJS) $(TEST_LDFLAGS) $(TEST_LDLIBS)

ifndef BUILD_SHARED
$(VAL_BIN): override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
$(VAL_BIN): $(VAL_OBJS) $(LIB_STATIC)
else
$(VAL_BIN): $(VAL_OBJS) $(LIB_SHARED)
endif
	$(CXX) -o $@ $(VAL_OBJS) $(VAL_LDFLAGS) $(VAL_LDLIBS)

bin/c_example bin/src/enc bin/src/lib bin/src/val bin/test:
	$(MKDIR) -p $@

clean:
	$(RM) -r bin/*

.PHONY: all cex cex clean debug enc lib-shared lib-static perf shared static test test val

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
