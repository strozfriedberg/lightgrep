ACLOCAL_AMFLAGS = -I m4

AM_CPPFLAGS = -I$(srcdir)/include $(ICU_CPPFLAGS) $(BOOST_CPPFLAGS) $(LG_CPPFLAGS)
AM_CFLAGS = $(LG_CFLAGS) $(ASAN_CFLAGS)
AM_CXXFLAGS = $(STDCXX_CXXFLAGS) $(LG_CXXFLAGS) $(ICU_CXXFLAGS) $(BOOST_CXXFLAGS) $(ASAN_CXXFLAGS)
AM_LDFLAGS = $(ICU_LDFLAGS) $(BOOST_LDFLAGS) $(LG_LDFLAGS) $(ASAN_LDFLAGS)
AM_YFLAGS = -r solved

LG_LIB = src/lib/liblightgrep.la
LG_LIB_INT = src/lib/liblightgrepint.la

lib_LTLIBRARIES = $(LG_LIB)

if BUILD_DLL
src_lib_liblightgrep_la_SOURCES = src/lib/version.rc
else
src_lib_liblightgrep_la_SOURCES =
endif
nodist_EXTRA_src_lib_liblightgrep_la_SOURCES = dummy.cpp # forces C++ linking

noinst_LTLIBRARIES = $(LG_LIB_INT)

src_lib_liblightgrepint_la_SOURCES = \
	include/automata.h \
	include/basic.h \
	include/boost_asio.h \
	include/boost_lexical_cast.h \
	include/boost_program_options.h \
	include/byteset.h \
	include/c_api_util.h \
	include/chain.h \
	include/codegen.h \
	include/compiler.h \
	include/decoders/asciidecoder.h \
	include/decoders/bytesource.h \
	include/decoders/decoder.h \
	include/decoders/decoderfactory.h \
	include/decoders/ocedecoder.h \
	include/decoders/rotdecoder.h \
	include/decoders/utf16.h \
	include/decoders/utf16decoder.h \
	include/decoders/utf32.h \
	include/decoders/utf32decoder.h \
	include/decoders/utf8.h \
	include/decoders/utf8decoder.h \
	include/decoders/utfdecoderbase.h \
	include/decoders/xordecoder.h \
	include/encoders/ascii.h \
	include/encoders/byteencoder.h \
	include/encoders/caching_encoder.h \
	include/encoders/charencoder.h \
	include/encoders/concrete_encoders.h \
	include/encoders/decorating_encoder.h \
	include/encoders/encoder.h \
	include/encoders/encoderbase.h \
	include/encoders/encoderfactory.h \
	include/encoders/oceencoder.h \
	include/encoders/rotencoder.h \
	include/encoders/utf16.h \
	include/encoders/utf32.h \
	include/encoders/utf8.h \
	include/encoders/utfbase.h \
	include/encoders/xorencoder.h \
	include/errors.h \
	include/factor_analysis.h \
	include/fragment.h \
	include/fsmthingy.h \
	include/fwd_pointers.h \
	include/graph.h \
	include/handles.h \
	include/hitwriter.h \
	include/instructions.h \
	include/lg_app.h \
	include/matchgen.h \
	include/nfabuilder.h \
	include/nfaoptimizer.h \
	include/options.h \
	include/optparser.h \
	include/ostream_join_iterator.h \
	include/parsenode.h \
	include/parser.h \
	include/parsetree.h \
	include/parseutil.h \
	include/pattern.h \
	include/pattern_map.h \
	include/program.h \
	include/rangeset.h \
	include/reader.h \
	include/rewriter.h \
	include/searchcontroller.h \
	include/searchhit.h \
	include/sequences.h \
	include/simplevectorfamily.h \
	include/sparseset.h \
	include/states.h \
	include/staticvector.h \
	include/thread.h \
	include/timer.h \
	include/transition.h \
	include/transitionfactory.h \
	include/unicode.h \
	include/unparser.h \
	include/util.h \
	include/utility.h \
	include/vectorfamily.h \
	include/vm.h \
	include/vm_interface.h \
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
	src/lib/errors.cpp \
	src/lib/fsmthingy.cpp \
	src/lib/instructions.cpp \
	src/lib/lightgrep_c_api.cpp \
	src/lib/lightgrep_c_util.cpp \
	src/lib/matchgen.cpp \
	src/lib/nfabuilder.cpp \
	src/lib/nfaoptimizer.cpp \
	src/lib/oceencoder.cpp \
	src/lib/parsenode.cpp \
	src/lib/parser.cpp \
	src/lib/pattern_map.cpp \
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

if HAVE_ICU
src_lib_liblightgrepint_la_SOURCES += \
	include/decoders/icudecoder.h \
	include/encoders/icuencoder.h \
	include/icuconverter.h \
	include/icuutil.h \
	src/lib/icuconverter.cpp \
	src/lib/icuencoder.cpp \
	src/lib/icuutil.cpp
endif

# TODO: Figure out how to build internal testing utilities
# without exporting all C++ classes
# src_lib_liblightgrep_la_LDFLAGS = -export-symbols-regex '^lg_'

src_lib_liblightgrep_la_LIBADD = $(LG_LIB_INT) $(ICU_LIBS) $(STDCXX_LIB)
if BUILD_DLL
src_lib_liblightgrep_la_LDFLAGS = $(AM_LDFLAGS) $(LG_LIB_LDFLAGS) -avoid-version
else
src_lib_liblightgrep_la_LDFLAGS = $(AM_LDFLAGS) $(LG_LIB_LDFLAGS)
endif

src_lib_liblightgrep_ladir = $(includedir)/lightgrep

src_lib_liblightgrep_la_HEADERS = \
	include/lightgrep/transforms.h \
	include/lightgrep/api.h \
	include/lightgrep/encodings.h \
	include/lightgrep/util.h \
	include/lightgrep/search_hit.h

noinst_PROGRAMS = \
	examples/c_example/cex

if HAVE_ICU
noinst_PROGRAMS += \
	src/enc/enc \
	src/val/val \
	src/what/what
endif

examples_c_example_cex_SOURCES = examples/c_example/main.c
examples_c_example_cex_LDADD = $(LG_LIB) $(ICU_LIBS) $(STDCXX_LIB)

if HAVE_ICU
src_enc_enc_SOURCES = src/enc/encodings.cpp
src_enc_enc_LDADD = $(ICU_LIBS) $(STDCXX_LIB)

src_val_val_SOURCES = src/val/valid.cpp
src_val_val_LDADD = $(LG_LIB_INT) $(ICU_LIBS) $(STDCXX_LIB)

src_what_what_SOURCES = src/what/what.cpp
src_what_what_LDADD = $(LG_LIB_INT) $(ICU_LIBS) $(STDCXX_LIB)
endif

if HAVE_ICU
$(srcdir)/include/lightgrep/encodings.h: src/enc/enc$(EXEEXT)
	$(LOG_COMPILER) src/enc/enc$(EXEEXT) >$@
else
$(srcdir)/include/lightgrep/encodings.h: include/lightgrep/encodings.h.no_icu
	cp $< $@
endif

BUILT_SOURCES = include/lightgrep/encodings.h

bin_PROGRAMS = src/cmd/lightgrep

src_cmd_lightgrep_SOURCES = \
	src/cmd/hitwriter.cpp \
	src/cmd/lg_app.cpp \
	src/cmd/main.cpp \
	src/cmd/optparser.cpp \
	src/cmd/options.cpp \
	src/cmd/reader.cpp \
	src/cmd/searchcontroller.cpp \
	src/cmd/util.cpp
	
src_cmd_lightgrep_LDADD = $(LG_LIB) $(LG_LIBS) $(ICU_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_ASIO_LIB) $(GPT_LIBS) $(STDCXX_LIB)

if BUILD_MINGW

src_cmd_lightgrep_SOURCES += src/cmd/version.rc

# assume rc files are UTF-8 (Windows codepage 65001)
RCFLAGS = -c 65001

LTRCCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=RC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=compile $(RC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(filter-out -mthreads,$(AM_CPPFLAGS) $(CPPFLAGS)) $(RCFLAGS)

.rc.o:
	$(LTRCCOMPILE) -i $< -o $@
	[ -f $@ ] || cp $(@D)/.libs/$(@F) $@

src/cmd/.libs/version.o: config.h
src/cmd/version.o: config.h

endif

@VALGRIND_CHECK_RULES@

TEST_EXTENSIONS = .sh
SH_LOG_COMPILER =

AM_TESTS_ENVIRONMENT = builddir=`pwd`;

check_PROGRAMS = test/test

TESTS = test/test.sh

if BUILD_PYTHON
TESTS += pylightgrep/test.sh
endif

test_test_SOURCES = \
	src/cmd/hitwriter.cpp \
	src/cmd/lg_app.cpp \
	src/cmd/options.cpp \
	src/cmd/optparser.cpp \
	src/cmd/util.cpp \
	test/data_reader.cpp \
	test/data_reader.h \
	test/dtest.cpp \
	test/dtest.h \
	test/executor.h \
	test/mockcallback.cpp \
	test/mockcallback.h \
	test/stest.cpp \
	test/stest.h \
	test/test_ascii.cpp \
	test/test_auto_search_1.cpp \
	test/test_auto_search_2.cpp \
	test/test_auto_search_3.cpp \
	test/test_auto_search_4.cpp \
	test/test_auto_search_5.cpp \
	test/test_auto_search_6.cpp \
	test/test_auto_search_7.cpp \
	test/test_auto_search_multi_1.cpp \
	test/test_auto_search_multi_2.cpp \
	test/test_auto_starts_with_1.cpp \
	test/test_auto_starts_with_2.cpp \
	test/test_auto_starts_with_3.cpp \
	test/test_auto_starts_with_4.cpp \
	test/test_auto_starts_with_5.cpp \
	test/test_auto_starts_with_6.cpp \
	test/test_auto_starts_with_7.cpp \
	test/test_auto_starts_with_multi_1.cpp \
	test/test_auto_starts_with_multi_2.cpp \
	test/test_basic.cpp \
	test/test_byteset.cpp \
	test/test_bytesource.cpp \
	test/test_c_api.cpp \
	test/test_compiler.cpp \
	test/test_c_util.cpp \
	test/test_factor_analysis.cpp \
	test/test_graph.cpp \
	test/test_helper.cpp \
	test/test_helper.h \
	test/test_hitwriter.cpp \
	test/test_instructions.cpp \
	test/test_main.cpp \
	test/test_matchgen.cpp \
	test/test_nfabuilder.cpp \
	test/test_nfaoptimizer.cpp \
	test/test_oceencoder.cpp \
	test/test_options.cpp \
	test/test_optparser.cpp \
	test/test_parser.cpp \
	test/test_parsetree.cpp \
	test/test_parseutil.cpp \
	test/test_pattern_map.cpp \
	test/test_program.cpp \
	test/test_rangeset.cpp \
	test/test_rewriter.cpp \
	test/test_rotencoder.cpp \
	test/test_search_assertions.cpp \
	test/test_search.cpp \
	test/test_search_data.cpp \
	test/test_search_data_driver.cpp \
	test/test_search_switches.cpp \
	test/test_sequences.h \
	test/test_sparseset.cpp \
	test/test_starts_with.cpp \
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
	test/test_vectorfamily.cpp \
	test/test_vm.cpp \
	test/test_xorencoder.cpp \
	test/unicode_sets.h \
	test/data/hectotest \
	test/data/hectotest.dat \
	test/data/kilotest \
	test/data/kilotest.dat \
	test/data/pats.0 \
	test/data/pats.1 \
	test/data/pats.2

if HAVE_ICU
test_test_SOURCES += \
	test/test_icu.cpp \
	test/test_icudecoder.cpp \
	test/test_icuutil.cpp
endif

test_test_CPPFLAGS = $(AM_CPPFLAGS) $(CATCH2_CPPFLAGS)
test_test_CFLAGS = $(AM_CFLAGS) $(CATCH2_CFLAGS)
test_test_LDADD = $(LG_LIB_INT) $(ICU_LIBS) $(BOOST_PROGRAM_OPTIONS_LIB) $(BOOST_ASIO_LIB) $(CATCH2_LIBS) $(STDCXX_LIB)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = lightgrep.pc

CLEANFILES = include/lightgrep/encodings.h src/cmd/version.lo

if BUILD_DLL
src/lib/.libs/version.o: config.h

# assume rc files are UTF-8 (Windows codepage 65001)
RCFLAGS = -c 65001

LTRCCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=RC $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=compile $(RC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(filter-out -mthreads,$(AM_CPPFLAGS) $(CPPFLAGS)) $(RCFLAGS)

.rc.lo:
	$(LTRCCOMPILE) -i $< -o $@
endif

#if BUILD_DLL
#msvclibdir = $(libdir)
#nodist_msvclib_DATA = src/lib/.libs/liblightgrep.lib
#
#src/lib/.libs/liblightgrep.lib: src/lib/.libs/liblightgrep-0.dll
#	$(DLLTOOL) -D $< -d src/lib/.libs/liblightgrep.def -l $@
#endif

install-exec-hook:
	$(RM) $(DESTDIR)$(libdir)/liblightgrep.la

# must be set before we can append to it
MOSTLYCLEANFILES =

#
# Java bindings
#
if BUILD_JAVA

lib_LTLIBRARIES += src/java/jni/libjlightgrep.la

src_java_jni_libjlightgrep_la_SOURCES = src/java/jni/jlightgrep.cpp

src_java_jni_libjlightgrep_la_CPPFLAGS = -I$(srcdir)/include $(JNI_CPPFLAGS) $(LG_CPPFLAGS)
src_java_jni_libjlightgrep_la_CXXFLAGS = $(STDCXX_CXXFLAGS) $(LG_CXXFLAGS)
src_java_jni_libjlightgrep_la_LDFLAGS = $(LG_LDFLAGS) -module -avoid-version
src_java_jni_libjlightgrep_la_LIBADD = $(LG_LIB) $(STDCXX_LIB)

JROOT:=src/java
JSRC_DIR:=$(JROOT)/src/main/java
JNI_DIR:=$(JROOT)/jni
JPKG_DIR:=com/lightboxtechnologies/lightgrep

SRC_SOURCE_FILES:=\
	$(JSRC_DIR)/$(JPKG_DIR)/ContextHandle.java \
	$(JSRC_DIR)/$(JPKG_DIR)/ContextOptions.java \
	$(JSRC_DIR)/$(JPKG_DIR)/DecoderHandle.java \
	$(JSRC_DIR)/$(JPKG_DIR)/FSMHandle.java \
  $(JSRC_DIR)/$(JPKG_DIR)/Handle.java \
	$(JSRC_DIR)/$(JPKG_DIR)/HitCallback.java \
	$(JSRC_DIR)/$(JPKG_DIR)/HitContext.java \
	$(JSRC_DIR)/$(JPKG_DIR)/KeyOptions.java \
	$(JSRC_DIR)/$(JPKG_DIR)/KeywordException.java \
	$(JSRC_DIR)/$(JPKG_DIR)/LGUtil.java \
	$(JSRC_DIR)/$(JPKG_DIR)/LibraryLoader.java \
	$(JSRC_DIR)/$(JPKG_DIR)/PatternHandle.java \
	$(JSRC_DIR)/$(JPKG_DIR)/PatternInfo.java \
	$(JSRC_DIR)/$(JPKG_DIR)/ProgramException.java \
	$(JSRC_DIR)/$(JPKG_DIR)/ProgramHandle.java \
	$(JSRC_DIR)/$(JPKG_DIR)/ProgramOptions.java \
	$(JSRC_DIR)/$(JPKG_DIR)/SearchHit.java \
	$(JSRC_DIR)/$(JPKG_DIR)/Throws.java

JNI_HEADER_FILES:=\
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_ContextHandle.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_DecoderHandle.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_FSMHandle.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_Handle.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_HitContext.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_KeyOptions.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_LGUtil.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_PatternHandle.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_PatternInfo.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_ProgramHandle.h \
	$(JNI_DIR)/com_lightboxtechnologies_lightgrep_ProgramOptions.h

$(JNI_HEADER_FILES): $(SRC_SOURCE_FILES)
	$(JAVAC) -h $(JNI_DIR) $^

.PRECIOUS: $(JNI_HEADER_FILES)

src/java/jni/jlightgrep.h: $(JNI_HEADER_FILES)
	for i in $(notdir $(JNI_HEADER_FILES)) ; do \
		echo "#include \"$$i\"" ; \
	done >$@

BUILT_SOURCES += src/java/jni/jlightgrep.h

noinst_jar_DATA = src/java/target/jlightgrep-0.0.1.jar
noinst_jardir = $(libdir)

src/java/target/jlightgrep-0.0.1.jar: src/java/jni/libjlightgrep.la
	pushd $(JROOT) ; ./mvnw package	; popd

MOSTLYCLEANFILES += src/java/jni/jlightgrep.h $(JNI_HEADER_FILES)

clean-local:
	pushd $(JROOT) ; ./mvnw clean ; popd

endif
