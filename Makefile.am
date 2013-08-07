ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -Iinclude
AM_YFLAGS = -r solved

LG_LIB = src/lib/liblightgrep.la
LG_LIB_INT = src/lib/liblightgrepint.la

lib_LTLIBRARIES = $(LG_LIB)

src_lib_liblightgrep_la_SOURCES =
nodist_EXTRA_src_lib_liblightgrep_la_SOURCES = dummy.cpp # forces C++ linking

noinst_LTLIBRARIES = $(LG_LIB_INT)

src_lib_liblightgrepint_la_SOURCES = \
	src/lib/ascii.cpp \
	src/lib/automata.cpp \
	src/lib/byteencoder.cpp \
	src/lib/byteset.cpp \
	src/lib/c_api_util.cpp \
	src/lib/chain.cpp \
	src/lib/charencoder.cpp \
	src/lib/codegen.cpp \
	src/lib/compiler.cpp \
	src/lib/encoderbase.cpp \
	src/lib/encoderfactory.cpp \
	src/lib/fsmthingy.cpp \
	src/lib/icuconverter.cpp \
	src/lib/icuencoder.cpp \
	src/lib/icuutil.cpp \
	src/lib/instructions.cpp \
	src/lib/lightgrep_c_api.cpp \
	src/lib/lightgrep_c_util.cpp \
	src/lib/matchgen.cpp \
	src/lib/nfabuilder.cpp \
	src/lib/nfaoptimizer.cpp \
	src/lib/oceencoder.cpp \
	src/lib/parsenode.cpp \
	src/lib/parser.cpp \
	src/lib/re_grammar.ypp \
	src/lib/parsetree.cpp \
	src/lib/parseutil.cpp \
	src/lib/pattern.cpp \
	src/lib/program.cpp \
	src/lib/rewriter.cpp \
	src/lib/states.cpp \
	src/lib/thread.cpp \
	src/lib/unparser.cpp \
	src/lib/utf8.cpp \
	src/lib/utfbase.cpp \
	src/lib/utility.cpp \
	src/lib/vm.cpp \
	src/lib/decoders/decoder.cpp \
	src/lib/decoders/decoderfactory.cpp \
	src/lib/decoders/ocedecoder.cpp

src_lib_liblightgrep_la_LDFLAGS = -export-symbols-regex '^lg_'
src_lib_liblightgrep_la_LIBADD = $(LG_LIB_INT) $(ICU_LIBS) $(STDCXX_LIB)

src_lib_liblightgrep_ladir = $(includedir)/lightgrep

src_lib_liblightgrep_la_HEADERS = \
	include/lightgrep/transforms.h \
	include/lightgrep/api.h \
	include/lightgrep/encodings.h \
	include/lightgrep/util.h \
	include/lightgrep/search_hit.h

noinst_PROGRAMS = c_example/cex src/enc/enc src/val/val src/what/what

c_example_cex_SOURCES = c_example/main.c
c_example_cex_LDADD = $(LG_LIB) $(ICU_LIBS) $(STDCXX_LIB)

src_enc_enc_SOURCES = src/enc/encodings.cpp
src_enc_enc_LDADD = $(ICU_LIBS) $(STDCXX_LIB)

src_val_val_SOURCES = src/val/valid.cpp
src_val_val_LDADD = $(LG_LIB_INT) $(ICU_LIBS) $(STDCXX_LIB)

src_what_what_SOURCES = src/what/what.cpp
src_what_what_LDADD = $(LG_LIB_INT) $(ICU_LIBS) $(STDCXX_LIB)

check_PROGRAMS = test/test
TESTS = $(check_PROGRAMS)

test_test_SOURCES = \
	test/data_reader.cpp \
	test/dtest.cpp \
	test/mockcallback.cpp \
	test/stest.cpp \
	test/test.cpp \
	test/test_ascii.cpp \
	test/test_auto_searches_1.cpp \
	test/test_auto_searches_2.cpp \
	test/test_auto_searches_3.cpp \
	test/test_auto_searches_4.cpp \
	test/test_auto_searches_5.cpp \
	test/test_auto_searches_6.cpp \
	test/test_auto_searches_7.cpp \
	test/test_auto_searches_8.cpp \
	test/test_auto_searches_multi_1.cpp \
	test/test_auto_searches_multi_2.cpp \
	test/test_basic.cpp \
	test/test_byteset.cpp \
	test/test_bytesource.cpp \
	test/test_c_api.cpp \
	test/test_c_util.cpp \
	test/test_compiler.cpp \
	test/test_graph.cpp \
	test/test_helper.cpp \
	test/test_icu.cpp \
	test/test_icudecoder.cpp \
	test/test_icuutil.cpp \
	test/test_instructions.cpp \
	test/test_matchgen.cpp \
	test/test_nfabuilder.cpp \
	test/test_nfaoptimizer.cpp \
	test/test_oceencoder.cpp \
	test/test_ostream_join_iterator.cpp \
	test/test_parser.cpp \
	test/test_parseutil.cpp \
	test/test_program.cpp \
	test/test_rangeset.cpp \
	test/test_rewriter.cpp \
	test/test_rotencoder.cpp \
	test/test_search_data.cpp \
	test/test_searches.cpp \
	test/test_searches_data.cpp \
	test/test_sparseset.cpp \
	test/test_states.cpp \
	test/test_testregex_basic_modified.cpp \
	test/test_thread.cpp \
	test/test_transitionfactory.cpp \
	test/test_unicode.cpp \
	test/test_unparser.cpp \
	test/test_utf16.cpp \
	test/test_utf32.cpp \
	test/test_utf8.cpp \
	test/test_utf8decoder.cpp \
	test/test_utility.cpp \
	test/test_vm.cpp \
	test/test_xorencoder.cpp

test_test_CPPFLAGS = $(AM_CPPFLAGS) $(SCOPE_CPPFLAGS)
test_test_LDFLAGS = $(BOOST_LDFLAGS)
test_test_LDADD = $(LG_LIB_INT) $(BOOST_THREAD_LIB) $(BOOST_CHRONO_LIB) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_SYSTEM_LIB) $(BOOST_ASIO_LIB) $(ICU_LIBS) $(STDCXX_LIB)
