#
# Directories
#

SRCDIR=src

CEXDIR=c_example
CMDDIR=$(SRCDIR)/cmd
ENCDIR=$(SRCDIR)/enc
LIBDIR=$(SRCDIR)/lib
TESTDIR=test

BINDIR=bin
INCDIR=include

SRCDIRS=$(CEXDIR) $(CMDDIR) $(ENCDIR) $(LIBDIR) $(TESTDIR)
BUILDDIRS=$(addprefix $(BINDIR)/, $(SRCDIRS))

#
# Build programs and flags
#
CC=gcc
CXX=g++
BISON=bison
RANLIB=ranlib

override CPPFLAGS+=-MMD -MP
override CFLAGS+=-std=c11 -O3 -W -Wall -Wextra -pedantic -pipe
override CXXFLAGS+=-std=c++11 -O3 -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe
override INCLUDES+=-isystem vendors/scope -I$(INCDIR)
override LDFLAGS+=-static-libstdc++
override LDLIBS+=-L$(BINDIR)/$(LIBDIR)

#
# Determine locations for source, object, binary, and dependency files
#

MODULES=CEX CMD ENC LIB TEST

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

CEX_BINARY=$(BINDIR)/c_example/c_example
CEX_OBJECTS+=$(LIB_BINARY)
CEX_LIBS=-llightgrep -licuuc -licudata

CMD_BINARY=$(BINDIR)/$(CMDDIR)/lightgrep
CMD_OBJECTS+=$(LIB_BINARY)
CMD_LIBS=-lboost_system-mt -lboost_thread-mt -lboost_program_options-mt -lboost_filesystem-mt -llightgrep -licuuc -licudata -lpthread

ENC_BINARY=$(BINDIR)/$(ENCDIR)/encodings
ENC_LIBS=-licuuc -licudata

TEST_BINARY=$(BINDIR)/test/test
TEST_OBJECTS+=$(LIB_BINARY) $(BINDIR)/$(CMDDIR)/options.o $(BINDIR)/$(CMDDIR)/optparser.o
TEST_LIBS=-lboost_program_options-mt -llightgrep -licuuc -licudata

#
# Top-level targets
#

all: makedirs lib enc cmd c_example test

debug: CFLAGS+=-g
debug: CFLAGS:=$(filter-out -O3, $(CFLAGS))
debug: CXXFLAGS+=-g
debug: CXXFLAGS:=$(filter-out -O3, $(CXXFLAGS))
debug: all

c_example: $(CEX_BINARY) 

cmd: $(CMD_BINARY) 

enc: $(ENC_BINARY) 

lib: $(LIB_BINARY) 

test: $(TEST_BINARY)
	$(TEST_BINARY) --test

-include $(DEPS)

clean-objs:
	$(RM) $(BINDIR)/{$(CEXDIR),$(CMDDIR),$(LIBDIR),$(ENCDIR),$(TESTDIR)}/*.{o,a}

clean:
	$(RM) -r $(BINDIR)/*

.PHONY: all c_example clean debug enc lib makedirs test $(DEPS)

#
# Directory targets
#

makedirs: $(BUILDDIRS)

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

$(foreach m,LIB,$(eval $(call o-a-goal,$(m))))

define o-bin-goal
$($(1)_BINARY): $($(1)_OBJECTS)
	$$(CXX) -o $$@ $$(filter-out $(LIB_BINARY), $$^) $$(LDFLAGS) $($(1)_LDFLAGS) $$(LDLIBS) $($(1)_LIBS)
endef

$(foreach m,CEX CMD ENC TEST,$(eval $(call o-bin-goal,$(m))))

#
# Object targets
#

define c-o-goal
$(BINDIR)/$1/%.o: $1/%.c
	$$(CC) -o $$@ -c $$(CPPFLAGS) $$(CFLAGS) $$(INCLUDES) $$<
endef

define cpp-o-goal
$(BINDIR)/$1/%.o: $1/%.cpp
	$$(CXX) -o $$@ -c $$(CPPFLAGS) $$(CXXFLAGS) $$(INCLUDES) $$<
endef

$(foreach sdir,$(SRCDIRS),$(eval $(call c-o-goal,$(sdir))))
$(foreach sdir,$(SRCDIRS),$(eval $(call cpp-o-goal,$(sdir))))

$(BINDIR)/$(LIBDIR)/parser.tab.o: $(BINDIR)/$(LIBDIR)/parser.tab.cpp
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<

#
# Generated source files
#

$(BINDIR)/$(LIBDIR)/parser.tab.cpp: $(LIBDIR)/parser.ypp
	$(BISON) -r solved $< -o $@
