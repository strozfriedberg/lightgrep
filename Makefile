#
# Directories
#

SRCDIR=src

CEXDIR=c_example
CMDDIR=$(SRCDIR)/cmd
ENCDIR=$(SRCDIR)/enc
LIBDIR=$(SRCDIR)/lib
TESTDIR=test
VALDIR=$(SRCDIR)/val

BINDIR=bin
INCDIR=include

LIBMODS=LIB
BINMODS=CEX CMD ENC TEST VAL

MODULES=$(LIBMODS) $(BINMODS)

#
# Build programs and flags
#
CC=gcc
CXX=g++
BISON=bison
RANLIB=ranlib

override CPPFLAGS+=-MMD -MP
override CFLAGS+=-std=c1x -O3 -W -Wall -Wextra -pedantic -pipe
override CXXFLAGS+=-std=c++0x -O3 -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe
override INCLUDES+=-isystem vendors/boost -isystem vendors/icu -isystem vendors/scope -I$(INCDIR)
override LDFLAGS+=-static-libstdc++
override LDLIBS+=-Llib -L$(BINDIR)/$(LIBDIR)

BOOST_TYPE=-mt

#
# Determine the OS we are building on/for
#
UNAME_O=$(strip $(shell uname -o))
ifeq ($(UNAME_O),GNU/Linux)
IS_LINUX=1
else ifeq ($(UNAME_O),Msys)
IS_WINDOWS=1
endif

ifdef IS_WINDOWS
override CPPFLAGS+=-DPOLLUTE_GLOBAL_NAMESPACE_WITH_WINDOWS_H
ifdef IS_SHARED
override CPPFLAGS+=-DBOOST_THREAD_USE_LIB
endif
ifdef IS_WINDOWS_XP
override CPPFLAGS+=-D_WIN32_WINNT=0x0501
endif
override CXXFLAGS+=-mthreads
endif

#
# Determine locations for source, object, binary, and dependency files
#

# collect the source and build directories for the modules
SRCDIRS=$(foreach m,$(MODULES), $($(m)DIR))
BUILDDIRS=$(addprefix $(BINDIR)/, $(SRCDIRS))

# find all source files and generate object file names
define sources-and-objects
$(1)_SOURCES=$$(wildcard $$($(1)DIR)/*.cpp) $$(wildcard $$($(1)DIR)/*.c)
$(1)_OBJECTS=$$(patsubst %,$(BINDIR)/%.o,$$(basename $$($(1)_SOURCES)))
endef

$(foreach m,$(MODULES), $(eval $(call sources-and-objects,$(m))))

# generate names for the dependency files
DEPS=$(foreach m,$(MODULES), $($(m)_OBJECTS))
DEPS:=$(DEPS:%.o=%.d)

# name the binaries, extra objects, libraries, and flags for each module
LIB_BINARY=$(BINDIR)/$(LIBDIR)/liblightgrep.a
LIB_OBJECTS+=$(BINDIR)/$(LIBDIR)/parser.tab.o

CEX_BINARY=$(BINDIR)/$(CEXDIR)/c_example
CEX_OBJECTS+=$(LIB_BINARY)
CEX_LIBS=-llightgrep -licuuc -licudata

CMD_BINARY=$(BINDIR)/$(CMDDIR)/lightgrep
CMD_OBJECTS+=$(LIB_BINARY)
CMD_LIBS=-lboost_system$(BOOST_TYPE) -lboost_thread$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -lboost_filesystem$(BOOST_TYPE) -llightgrep -licuuc -licudata
ifdef IS_LINUX
CMD_LIBS+=-lpthread
else ifdef $(IS_WINDOWS)
CMD_LIBS+=-lws2_32 -lmswsock
endif

ENC_BINARY=$(BINDIR)/$(ENCDIR)/encodings
ENC_LIBS=-licuuc -licudata

VAL_BINARY=$(BINDIR)/$(VALDIR)/valid
VAL_OBJECTS+=$(LIB_BINARY)
VAL_LIBS=-llightgrep -licuuc -licudata

TEST_BINARY=$(BINDIR)/test/test
TEST_OBJECTS+=$(LIB_BINARY) $(BINDIR)/$(CMDDIR)/options.o $(BINDIR)/$(CMDDIR)/optparser.o
TEST_LIBS=-lboost_system$(BOOST_TYPE) -lboost_thread$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -llightgrep -licuuc -licudata
ifdef IS_LINUX
TEST_LIBS+=-lpthread
endif

#
# Top-level targets
#

all: lib enc cmd c_example test val

debug: CFLAGS+=-g
debug: CFLAGS:=$(filter-out -O3, $(CFLAGS))
debug: CXXFLAGS+=-g
debug: CXXFLAGS:=$(filter-out -O3, $(CXXFLAGS))
debug: all

trace: CPPFLAGS+=-DLBT_TRACE_ENABLED
trace: CXXFLAGS+=-g
trace: all

c_example: $(CEX_BINARY) 

cmd: $(CMD_BINARY)

enc: $(ENC_BINARY)

lib: $(LIB_BINARY) 

test: $(TEST_BINARY)
	$(TEST_BINARY) --test

val: $(VAL_BINARY)

-include $(DEPS)

clean:
	$(RM) -r $(BINDIR)/*

.PHONY: all c_example clean debug enc lib test trace val

#
# Directory targets
#

$(BUILDDIRS):
	mkdir -p $@

#
# Binary targets
#

define o-a-goal
$($(1)_BINARY): $($(1)_OBJECTS)
	$(AR) rc $$@ $$^
	$(RANLIB) $$@
endef

$(foreach m,$(LIBMODS),$(eval $(call o-a-goal,$(m))))

define o-bin-goal
$($(1)_BINARY): $($(1)_OBJECTS)
	$$(CXX) -o $$@ $$(filter-out $(LIB_BINARY), $$^) $$(LDFLAGS) $($(1)_LDFLAGS) $$(LDLIBS) $($(1)_LIBS)
endef

$(foreach m,$(BINMODS),$(eval $(call o-bin-goal,$(m))))

#
# Object targets
#

define c-o-goal
$(BINDIR)/$1/%.o: $1/%.c | $(BINDIR)/$1
	$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$(INCLUDES) $$<
endef

define cpp-o-goal
$(BINDIR)/$1/%.o: $1/%.cpp | $(BINDIR)/$1
	$$(CXX) -o $$@ -c $$(CPPFLAGS) $$(CXXFLAGS) $$(INCLUDES) $$<
endef

$(foreach sdir,$(SRCDIRS),$(eval $(call c-o-goal,$(sdir))))
$(foreach sdir,$(SRCDIRS),$(eval $(call cpp-o-goal,$(sdir))))

$(BINDIR)/$(LIBDIR)/parser.tab.o: $(BINDIR)/$(LIBDIR)/parser.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<

#
# Generated source files
#

$(BINDIR)/$(LIBDIR)/parser.tab.cpp: $(LIBDIR)/parser.ypp | $(@D)
	$(BISON) -r solved $< -o $@
