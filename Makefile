.SUFFIXES:

PREFIX=/usr/local

#
# Set OS-specific variables 
#
UNAME_S=$(strip $(shell uname -s))
ifeq ($(UNAME_S),Linux)
  IS_LINUX=1
  include Makefile.linux.conf
else ifeq ($(UNAME_S:MINGW%=MINGW),MINGW)
  IS_WINDOWS=1
  include Makefile.windows.conf
else ifeq ($(UNAME_S),Darwin)
  IS_MACOSX=1
  include Makefile.darwin.conf
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

override INCLUDES+=-I$(LG_INCDIR) -I$(BOOST_INCDIR) -I$(ICU_INCDIR) -Iinclude
override CPPFLAGS+=-MMD -MP
override CFLAGS+=-std=c1x -W -Wall -Wextra -pedantic -pipe
override CXXFLAGS+=-std=c++0x -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe

#
# Other programs
#
MKDIR=mkdir


ifneq ($(BUILD_SHARED),1)
  override LDFLAGS+=-static-libstdc++ -static-libgcc -static
  override LDLIBS+=-ldl
endif

BOOST_LDFLAGS=-L$(BOOST_LIBDIR)
BOOST_LDLIBS=-lboost_thread$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -lboost_filesystem$(BOOST_TYPE) -lboost_system$(BOOST_TYPE)

ICU_LDFLAGS=-L$(ICU_LIBDIR)
ICU_LDLIBS=-licuuc -licudata

LG_LDFLAGS=-L$(LG_LIBDIR)
LG_LDLIBS=-llightgrep

#
# Setup for lightgrep
#
CMD_BIN=bin/src/cmd/lightgrep$(BINEXT)
CMD_SRCS=$(wildcard src/cmd/*.cpp)
CMD_OBJS=$(CMD_SRCS:%.cpp=bin/%.o)
CMD_INCLUDES=
CMD_CPPFLAGS=
CMD_CXXFLAGS=
CMD_LDFLAGS=$(LG_LDFLAGS) $(BOOST_LDFLAGS) $(ICU_LDFLAGS)
CMD_LDLIBS=$(LG_LDLIBS) $(BOOST_LDLIBS) $(ICU_LDLIBS)

ifdef IS_WINDOWS
  CMD_CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
endif

#
# Setup for test
#
TEST_BIN=bin/test/test$(BINEXT)
TEST_SRCS=$(wildcard test/*.cpp) src/cmd/optparser.cpp src/cmd/options.cpp
TEST_OBJS=$(TEST_SRCS:%.cpp=bin/%.o)
TEST_LIBS=
TEST_INCLUDES=-I$(SCOPE_INCDIR)
TEST_CPPFLAGS=
TEST_CXXFLAGS=
TEST_CFLAGS=
TEST_LDFLAGS=$(LG_LDFLAGS) $(BOOST_LDFLAGS) $(ICU_LDFLAGS)
TEST_LDLIBS=$(LG_LDLIBS) $(BOOST_LDLIBS) $(ICU_LDLIBS)

#
# Goals
#

all: cmd test

debug: override CXXFLAGS+=-g
debug: override CXXFLAGS:=$(filter-out -O3, $(CXXFLAGS))
ifndef IS_WINDOWS
debug: override CXXFLAGS+=-fstack-protector-all
endif
debug: all

perf: override CXXFLAGS+=-g
perf: all

cmd: $(CMD_BIN)

test: $(TEST_BIN)
	LD_LIBRARY_PATH=$(LG_LIBDIR):$(BOOST_LIBDIR):$(ICU_LIBDIR) $< --test

DEPS=$(patsubst %.o,%.d,$(CMD_OBJS) $(TEST_OBJS))

-include $(DEPS)

bin/src/cmd bin/test:
	$(MKDIR) -p $@

clean:
	$(RM) -r bin/*

.PHONY: all clean cmd test

#
# Patterns
#
.SECONDEXPANSION:
bin/%.o: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(LOCAL_CPPFLAGS) $(LOCAL_CXXFLAGS) $(LOCAL_INCLUDES) $<

define set-build-vars
$$($(1)_BIN): LOCAL_INCLUDES = $$(strip $$($(1)_INCLUDES) $$(INCLUDES))
$$($(1)_BIN): LOCAL_CPPFLAGS = $$(strip $$($(1)_CPPFLAGS) $$(CPPFLAGS))
$$($(1)_BIN): LOCAL_CXXFLAGS = $$(strip $$($(1)_CXXFLAGS) $$(CXXFLAGS))
$$($(1)_BIN): LOCAL_LDFLAGS  = $$(strip $$($(1)_LDFLAGS)  $$(LDFLAGS))
$$($(1)_BIN): LOCAL_LDLIBS   = $$(strip $$($(1)_LDLIBS)   $$(LDLIBS))
endef

define build-bin
$(call set-build-vars,$(1))
$$($(1)_BIN): $$($(1)_OBJS) $$($(1)_LIBS)
	$$(CXX) -o $$($(1)_BIN) $$($(1)_OBJS) $$(LOCAL_LDFLAGS) $$(LOCAL_LDLIBS)
endef

$(eval $(call build-bin,CMD))
$(eval $(call build-bin,TEST))
