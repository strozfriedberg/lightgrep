.SUFFIXES:

include Makefile.conf

#
# Set OS-specific variables 
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

#
# Library setup
#

# tell ICU if we link statically
ifneq ($(BUILD_SHARED),1)
  override CPPFLAGS+=-DU_STATIC_IMPLEMENTATION
endif

# tell boost::thread if we link statically
ifneq ($(BUILD_SHARED),1)
  override CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif

# -mthreads enables proper multithreaded exception handling on Windows
ifdef IS_WINDOWS
  override CXXFLAGS+=-mthreads
  override CFLAGS+=-mthreads
  override LDFLAGS+=-mthreads
endif

# * Linux uses pthreads.
# * Windows uses ws2_32, which in turn requires mswsock (wtf?!)
# * Mac OS X is apparently magical and needs no threading lib (?)
ifdef IS_LINUX
  override LDLIBS+=-lpthread
else ifdef IS_WINDOWS
  override LDLIBS+=-lws2_32 -lmswsock
endif

#LDFLAGS+=-Wl,--as-needed

# FIXME: How do we test for this?
#ifdef IS_WINDOWS_XP
#CPPFLAGS+=-D_WIN32_WINNT=0x0501
#endif

override INCLUDES+=-I$(BOOST_INCDIR) -I$(ICU_INCDIR) -Iinclude
override CPPFLAGS+=-MMD -MP
override CFLAGS+=-std=c1x -W -Wall -Wextra -pedantic -pipe
override CXXFLAGS+=-std=c++0x -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe

#
# Other programs
#
BISON=bison
RANLIB=ranlib
MKDIR=mkdir


ifneq ($(BUILD_SHARED),1)
  override LDFLAGS+=-static-libstdc++ -static-libgcc -static
endif

BOOST_INCLUDES=-I$(BOOST_INCDIR)
BOOST_LDFLAGS=-L$(BOOST_LIBDIR)
BOOST_LDLIBS=-lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -lboost_system$(BOOST_TYPE)

ICU_LDFLAGS=-L$(ICU_LIBDIR)
ICU_LDLIBS=-licuuc -licudata
ICU_STATIC_LDLIBS=-ldl -lm

LG_LDFLAGS=-Lbin/src/lib
LG_LDLIBS=-llightgrep

#
# Setup for liblightgrep
#
LIB_SRCS=$(wildcard src/lib/*.cpp)

LIB_LDLIBS=$(ICU_LDLIBS)
LIB_LDFLAGS=-L$(ICU_LIBDIR)

LIB_SHARED_BIN=bin/src/lib/liblightgrep$(SHARED_LIB_EXT)
LIB_SHARED_OBJS=$(LIB_SRCS:%.cpp=bin/%.os) bin/src/lib/parser.tab.os
LIB_SHARED_LIBS=
LIB_SHARED_INCLUDES=
LIB_SHARED_CPPFLAGS=
LIB_SHARED_CXXFLAGS=
LIB_SHARED_CFLAGS=
LIB_SHARED_LDFLAGS=-shared -fPIC $(LIB_LDFLAGS)
LIB_SHARED_LDLIBS=$(LIB_LDLIBS)

LIB_STATIC_BIN=bin/src/lib/liblightgrep$(STATIC_LIB_EXT)
LIB_STATIC_OBJS=$(LIB_SHARED_OBJS:%.os=%.o)
LIB_STATIC_LIBS=
LIB_STATIC_INCLUDES=
LIB_STATIC_CPPFLAGS=-DU_STATIC_IMPLEMENTATION -DBOOST_THREAD_USE_LIB
LIB_STATIC_CXXFLAGS=
LIB_STATIC_CFLAGS=
LIB_STATIC_LDFLAGS=$(LIB_LDFLAGS)
LIB_STATIC_LDLIBS=$(LIB_LDLIBS)

ifeq ($(BUILD_SHARED),1)
  LIB_BIN=$(LIB_SHARED_BIN)
else
  LIB_BIN=$(LIB_STATIC_BIN)
endif

ifndef IS_WINDOWS
  LIB_SHARED_CXXFLAGS+=-fPIC
endif

#
# Setup for test
#
TEST_BIN=bin/test/test$(BINEXT)
TEST_SRCS=$(wildcard test/*.cpp)
TEST_OBJS=$(TEST_SRCS:%.cpp=bin/%.o)
TEST_LIBS=$(LIB_BIN)
TEST_INCLUDES=-Itest -I$(SCOPE_INCDIR)
TEST_CPPFLAGS=
TEST_CXXFLAGS=
TEST_CFLAGS=
TEST_LDFLAGS=$(BOOST_LDFLAGS) $(ICU_LDFLAGS) $(LG_LDFLAGS)
TEST_LDLIBS=$(LG_LDLIBS) $(BOOST_LDLIBS) $(ICU_LDLIBS)

ifdef IS_WINDOWS
  TEST_CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
endif

#
# Setup for enc
#
ENC_BIN=bin/src/enc/encodings$(BINEXT)
ENC_SRCS=$(wildcard src/enc/*.cpp)
ENC_OBJS=$(ENC_SRCS:%.cpp=bin/%.o)
ENC_LIBS=
ENC_INCLUDES=
ENC_CPPFLAGS=
ENC_CXXFLAGS=
ENC_CFLAGS=
ENC_LDFLAGS=$(ICU_LDFLAGS)
ENC_LDLIBS=$(ICU_LDLIBS)

#
# Setup for val
#
VAL_BIN=bin/src/val/valid$(BINEXT)
VAL_SRCS=$(wildcard src/val/*.cpp)
VAL_OBJS=$(VAL_SRCS:%.cpp=bin/%.o)
VAL_LIBS=$(LIB_BIN)
VAL_INCLUDES=
VAL_CPPFLAGS=
VAL_CXXFLAGS=
VAL_CFLAGS=
VAL_LDFLAGS=$(LG_LDFLAGS) $(ICU_LDFLAGS)
VAL_LDLIBS=$(LG_LDLIBS) $(ICU_LDLIBS)

#
# Setup for c_example
#
CEX_BIN=bin/c_example/main$(BINEXT)
CEX_SRCS=$(wildcard c_example/*.c)
CEX_OBJS=$(CEX_SRCS:%.c=bin/%.o)
CEX_LIBS=$(LIB_BIN)
CEX_INCLUDES=
CEX_CPPFLAGS=
CEX_CXXFLAGS=
CEX_CFLAGS=
CEX_LDFLAGS=$(LG_LDFLAGS) $(ICU_LDFLAGS)
CEX_LDLIBS=$(LG_LDLIBS) $(ICU_LDLIBS)

#
# Goals
#

ALL=cex enc test val

ifeq ($(BUILD_SHARED),1)
  ALL+=lib-shared
endif

ifeq ($(BUILD_STATIC),1)
  ALL+=lib-static
endif

all: $(ALL) 

debug: override CFLAGS+=-g
debug: override CFLAGS:=$(filter-out -O3, $(CFLAGS))
debug: override CXXFLAGS+=-g
debug: override CXXFLAGS:=$(filter-out -O3, $(CXXFLAGS))
ifndef IS_WINDOWS
debug: override CXXFLAGS+=-fstack-protector-all
endif
debug: all

perf: override CFLAGS+=-g
perf: override CXXFLAGS+=-g
perf: all

cex: $(CEX_BIN)

enc: $(ENC_BIN)

lib-shared: $(LIB_SHARED_BIN)

lib-static: $(LIB_STATIC_BIN)

test: $(TEST_BIN)
	LD_LIBRARY_PATH=$(BOOST_LIBDIR):$(ICU_LIBDIR):bin/src/lib $< --test

val: $(VAL_BIN)

DEPS=$(patsubst %.o,%.d,$(CEX_OBJS) $(ENC_OBJS) $(LIB_STATIC_OBJS) $(TEST_OBJS) $(VAL_OBJS)) $(LIB_SHARED_OBJS:%.os=%.d)

-include $(DEPS)

bin/c_example bin/src/enc bin/src/lib bin/src/val bin/test:
	$(MKDIR) -p $@

clean:
	$(RM) -r bin/*

.PHONY: all cex cex clean debug enc lib-shared lib-static perf test val

#
# Patterns
#
.SECONDEXPANSION:
bin/%.o: %.c | $$(@D)
	$(CC) -o $@ -c $(LOCAL_CPPFLAGS) $(LOCAL_CFLAGS) $(LOCAL_INCLUDES) $<

.SECONDEXPANSION:
bin/%.os: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(LOCAL_CPPFLAGS) $(LOCAL_CXXFLAGS) $(LOCAL_INCLUDES) $<

.SECONDEXPANSION:
bin/%.o: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(LOCAL_CPPFLAGS) $(LOCAL_CXXFLAGS) $(LOCAL_INCLUDES) $<

.SECONDEXPANSION:
bin/%.tab.cpp: %.ypp | $$(@D)
	$(BISON) -r solved $< -o $@

.PRECIOUS: bin/%.tab.cpp

%.tab.os: %.tab.cpp
	$(CXX) -o $@ -c $(LOCAL_CPPFLAGS) $(LOCAL_CXXFLAGS) $(LOCAL_INCLUDES) $<

%.tab.o: %.tab.cpp
	$(CXX) -o $@ -c $(LOCAL_CPPFLAGS) $(LOCAL_CXXFLAGS) $(LOCAL_INCLUDES) $<

define set-build-vars
$$($(1)_BIN): LOCAL_INCLUDES = $$(strip $$($(1)_INCLUDES) $$(INCLUDES))
$$($(1)_BIN): LOCAL_CPPFLAGS = $$(strip $$($(1)_CPPFLAGS) $$(CPPFLAGS))
$$($(1)_BIN): LOCAL_CXXFLAGS = $$(strip $$($(1)_CXXFLAGS) $$(CXXFLAGS))
$$($(1)_BIN): LOCAL_CFLAGS   = $$(strip $$($(1)_CFLAGS)   $$(CFLAGS))
$$($(1)_BIN): LOCAL_LDFLAGS  = $$(strip $$($(1)_LDFLAGS)  $$(LDFLAGS))
$$($(1)_BIN): LOCAL_LDLIBS   = $$(strip $$($(1)_LDLIBS)   $$(LDLIBS))
endef

define build-bin
$(call set-build-vars,$(1))
$$($(1)_BIN): $$($(1)_OBJS) $$($(1)_LIBS)
	$$(CXX) -o $$($(1)_BIN) $$($(1)_OBJS) $$(LOCAL_LDFLAGS) $$(LOCAL_LDLIBS)
endef

define build-static-lib
$(call set-build-vars,$(1))
$$($(1)_BIN): $$($(1)_OBJS)
	$$(AR) rc $$@ $$^
	$$(RANLIB) $$@
endef

#$(info $(call build-exe,ENC))

$(eval $(call build-bin,CEX))
$(eval $(call build-bin,ENC))
$(eval $(call build-bin,TEST))
$(eval $(call build-bin,VAL))
$(eval $(call build-bin,LIB_SHARED))
$(eval $(call build-static-lib,LIB_STATIC))
