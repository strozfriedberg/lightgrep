ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -Iinclude

bin_PROGRAMS = src/cmd/lightgrep

src_cmd_lightgrep_SOURCES = \
	src/cmd/searchcontroller.cpp \
	src/cmd/main.cpp \
	src/cmd/server.cpp \
	src/cmd/optparser.cpp \
	src/cmd/hitwriter.cpp \
	src/cmd/options.cpp
	
src_cmd_lightgrep_LDFLAGS = $(BOOST_LDFLAGS)
# FIXME: LG_LIB is not being set
src_cmd_lightgrep_LDADD = $(LG_LIB) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_CHRONO_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_SYSTEM_LIB) $(BOOST_ASIO_LIB) $(ICU_LIBS) $(STDCXX_LIB)

check_PROGRAMS = test/test

test_test_SOURCES = \
	src/cmd/optparser.cpp \
	src/cmd/options.cpp \
	test/test.cpp \
	test/test_optparser.cpp \
	test/test_matchgen.cpp \
	test/test_hitwriter.cpp \
	test/test_options.cpp

test_test_CPPFLAGS = $(AM_CPPFLAGS) $(SCOPE_CPPFLAGS)
test_test_LDFLAGS = $(BOOST_LDFLAGS)
test_test_LDADD = $(LG_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(ICU_LIBS) $(STDCXX_LIB)

TESTS = $(check_PROGRAMS)
