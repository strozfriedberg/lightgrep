ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -Iinclude $(BOOST_CPPFLAGS) $(ICU_CPPFLAGS) $(LG_CPPFLAGS) 
AM_CXXFLAGS = $(STDCXX_CXXFLAGS) $(LG_CXXFLAGS) $(ICU_CXXFLAGS) $(BOOST_CXXFLAGS)
AM_LDFLAGS = $(LG_LDFLAGS) $(BOOST_LDFLAGS)

bin_PROGRAMS = src/cmd/lightgrep

src_cmd_lightgrep_SOURCES = \
	src/cmd/hitwriter.cpp \
	src/cmd/main.cpp \
	src/cmd/optparser.cpp \
	src/cmd/options.cpp \
	src/cmd/reader.cpp \
	src/cmd/searchcontroller.cpp \
	src/cmd/server.cpp \
	src/cmd/util.cpp
	
src_cmd_lightgrep_LDADD = $(LG_LIBS) $(BOOST_FILESYSTEM_LIB) $(BOOST_THREAD_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_SYSTEM_LIB) $(BOOST_ASIO_LIB) $(ICU_LIBS) $(STDCXX_LIB)

check_PROGRAMS = test/test

test_test_SOURCES = \
	src/cmd/hitwriter.cpp \
	src/cmd/optparser.cpp \
	src/cmd/options.cpp \
	src/cmd/util.cpp \
	test/test.cpp \
	test/test_optparser.cpp \
	test/test_matchgen.cpp \
	test/test_hitwriter.cpp \
	test/test_options.cpp

test_test_CPPFLAGS = $(AM_CPPFLAGS) $(SCOPE_CPPFLAGS)
test_test_LDADD = $(LG_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(ICU_LIBS) $(STDCXX_LIB)

TESTS = $(check_PROGRAMS)
