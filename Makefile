.SUFFIXES:

BOOST_INCDIR=vendors/boost_1_51_0
BOOST_LIBDIR=vendors/lib
BOOST_TYPE=

ICU_INCDIR=vendors/icu/include
ICU_LIBDIR=vendors/lib

SCOPE_INCDIR=vendors/scope

LG_INCDIR=vendors/liblightgrep/include
LG_LIBDIR=vendors/liblightgrep/bin/src/lib


MKDIR=mkdir

CXX=g++

CPPFLAGS=-MMD -MP
CXXFLAGS=-std=c++0x -W -Wall -Wextra -Wnon-virtual-dtor -pedantic -pipe

INCLUDES=$(addprefix -isystem ,$(sort $(BOOST_INCDIR) $(ICU_INCDIR) $(SCOPE_INCDIR))) -Iinclude -I$(LG_INCDIR)



LDFLAGS=$(addprefix -L,$(sort $(BOOST_LIBDIR) $(ICU_LIBDIR) $(LG_LIBDIR)))
LDLIBS=-llightgrep -lboost_thread$(BOOST_TYPE) -lboost_chrono$(BOOST_TYPE) -lboost_program_options$(BOOST_TYPE) -lboost_system$(BOOST_TYPE) -lboost_filesystem$(BOOST_TYPE) -licuuc -licudata -lpthread

CMD_SRCS=$(wildcard src/cmd/*.cpp)
CMD_OBJS=$(CMD_SRCS:%.cpp=bin/%.o)
CMD_SHARED_BIN=bin/src/cmd/lightgrep_shared
CMD_STATIC_BIN=bin/src/cmd/lightgrep_static
CMD_SHARED_LDFLAGS=$(LDFLAGS)
CMD_STATIC_LDFLAGS=-static-libstdc++ -static-libgcc -static $(LDFLAGS)
CMD_SHARED_LDLIBS=$(LDLIBS)
CMD_STATIC_LDLIBS=$(CMD_SHARED_LDLIBS) -ldl

TEST_SRCS=$(wildcard test/*.cpp) src/cmd/optparser.cpp src/cmd/options.cpp
TEST_OBJS=$(TEST_SRCS:%.cpp=bin/%.o)
TEST_SHARED_BIN=bin/test/test_shared
TEST_STATIC_BIN=bin/test/test_static
TEST_SHARED_LDFLAGS=$(LDFLAGS)
TEST_STATIC_LDFLAGS=-static-libstdc++ -static-libgcc -static $(LDFLAGS)
TEST_SHARED_LDLIBS=$(LDLIBS)
TEST_STATIC_LDLIBS=$(TEST_SHARED_LDLIBS) -ldl


all: shared static

shared: cmd-shared test-shared

static: cmd-static test-static

cmd-shared: $(CMD_SHARED_BIN)

cmd-static: $(CMD_STATIC_BIN)

test-shared: $(TEST_SHARED_BIN)
	LD_LIBRARY_PATH=$(BOOST_LIBDIR):$(ICU_LIBDIR):$(LG_LIBDIR) $< --test

test-static: $(TEST_STATIC_BIN)
	$< --test

DEPS=$(patsubst %.o,%.d,$(CMD_OBJS) $(TEST_OBJS))

-include $(DEPS)

$(CMD_SHARED_BIN): $(CMD_OBJS)
	$(CXX) -o $@ $(CMD_OBJS) $(CMD_SHARED_LDFLAGS) $(CMD_SHARED_LDLIBS)

$(CMD_STATIC_BIN): $(CMD_OBJS)
	$(CXX) -o $@ $(CMD_OBJS) $(CMD_STATIC_LDFLAGS) $(CMD_STATIC_LDLIBS)

$(TEST_SHARED_BIN): $(TEST_OBJS)
	$(CXX) -o $@ $(TEST_OBJS) $(TEST_SHARED_LDFLAGS) $(TEST_SHARED_LDLIBS)

$(TEST_STATIC_BIN): $(TEST_OBJS)
	$(CXX) -o $@ $(TEST_OBJS) $(TEST_STATIC_LDFLAGS) $(TEST_STATIC_LDLIBS)

bin/src/cmd bin/test:
	$(MKDIR) -p $@

clean:
	$(RM) -r bin/*

.PHONY: all clean cmd-shared cmd-static shared static test-shared test-static

.SECONDEXPANSION:
bin/%.o: %.cpp | $$(@D)
	$(CXX) -o $@ -c $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) $<
