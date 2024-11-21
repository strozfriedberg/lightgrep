/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <catch2/catch_test_macros.hpp>

#include "lightgrep/api.h"

#include <algorithm>
#include <cstring>
#include <memory>

#include <iostream>

#include "pattern_map.h"
#include "stest.h"
#include "handles.h"

// #include "basic.h"

// TODO: complete this test?

/*
TEST_CASE("testDedupeOnDiffEncodings") {
  std::shared_ptr<ParserHandle> parser(lg_create_parser(0), lg_destroy_parser);
  LG_KeyOptions opts;
  opts.FixedString = 1;
  opts.CaseInsensitive = 0;
  opts.UnicodeMode = 0;
  LG_Error** err = nullptr;

  lg_add_keyword(parser.get(), "apple", 0, &opts, "ASCII", err);
  lg_add_keyword(parser.get(), "apple", 0, &opts, "UTF-8", err);

  LG_ProgramOptions progOpts;
  progOpts.DeterminizeDepth = std::numeric_limits<uint32_t>::max();

  std::shared_ptr<ProgramHandle> prog(
    lg_create_program(parser.get(), &progOpts),
    lg_destroy_program
  );

  std::shared_ptr<ContextHandle> ctx(
    lg_create_context(prog.get(), 0),
    lg_destroy_context
  );
}
*/

TEST_CASE("testParsePatternWithBadPattern") {
  const std::string s = "*test";
  const LG_KeyOptions keyOpts{0, 0, 0};
  LG_Error* errPtr = nullptr;

  std::unique_ptr<PatternHandle, void(*)(PatternHandle*)> pat(
    lg_create_pattern(),
    lg_destroy_pattern
  );

  const int result = lg_parse_pattern(pat.get(), s.c_str(), &keyOpts, &errPtr);

  REQUIRE(keyOpts.FixedString == 0);
  REQUIRE(result == 0);
  REQUIRE(errPtr);
  REQUIRE(errPtr->Message);
  REQUIRE(!errPtr->EncodingChain);
  REQUIRE(!errPtr->Source);
  REQUIRE(errPtr->Index == -1);
  REQUIRE(errPtr->Pattern);
  REQUIRE(std::string(errPtr->Pattern) == s);

  lg_free_error(errPtr);
}

TEST_CASE("testAddPatternWithBadPattern") {
  const std::string s = "\\x{2642}";
  const std::string enc = "ASCII";
  const LG_KeyOptions keyOpts{0, 0, 0};
  LG_Error* errPtr = nullptr;

  std::unique_ptr<PatternHandle, void(*)(PatternHandle*)> pat(
    lg_create_pattern(),
    lg_destroy_pattern
  );

  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0, 0),
    lg_destroy_fsm
  );

  const int result = lg_parse_pattern(pat.get(), s.c_str(), &keyOpts, &errPtr);
  REQUIRE(result == 1);

  const int tree = lg_add_pattern(fsm.get(), pat.get(), enc.c_str(), 0, &errPtr);
  REQUIRE(tree < 0);

  REQUIRE(std::string(errPtr->Message) == "code point U+2642 does not exist in ASCII");
  REQUIRE(errPtr->Pattern);
  REQUIRE(std::string(errPtr->Pattern) == s);
  REQUIRE(errPtr->EncodingChain);
  REQUIRE(std::string(errPtr->EncodingChain) == enc);

  lg_free_error(errPtr);
}

TEST_CASE("testAddPatternListWithBadPatterns") {
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0, 0),
    lg_destroy_fsm
  );
  const char* badPatterns = "+badpattern\ngood\\d+pattern\n\\x{2642}\tASCII";
  const char* fileName = "/path/to/pattern/file";
  const char* defEnc[] = { "ASCII" };
  unsigned int defEncNum = 1;
  LG_KeyOptions keyOpts{0, 0, 0};
  LG_Error* errPtr = nullptr;

  const int result = lg_add_pattern_list(fsm.get(), badPatterns, fileName, defEnc, defEncNum, &keyOpts, &errPtr);

  LG_Error* headErrPtr = errPtr;

  REQUIRE(result == -1);
  REQUIRE(errPtr);
  REQUIRE(std::string(errPtr->Pattern) == "+badpattern");
  REQUIRE(!errPtr->EncodingChain);
  errPtr = errPtr->Next;
  REQUIRE(errPtr);
  REQUIRE(std::string(errPtr->Pattern) == "\\x{2642}");
  REQUIRE(std::string(errPtr->EncodingChain) == "ASCII");

  lg_free_error(headErrPtr);
}

TEST_CASE("testFreeErrorWithNull") {
  lg_free_error(nullptr);
}

TEST_CASE("testDestroyPatternWithNull") {
  lg_destroy_pattern(nullptr);
}

TEST_CASE("testParsePatternWithNull") {
  LG_KeyOptions keyOpts;
  LG_Error* errPtr = nullptr;

  int result = lg_parse_pattern(nullptr, "foo", &keyOpts, &errPtr);
  REQUIRE(result == 0);
  REQUIRE(errPtr);
  REQUIRE(0 == std::strcmp(errPtr->Message, "hPattern parameter was null. Use lg_create_pattern() to allocate."));
  lg_free_error(errPtr);

  std::unique_ptr<PatternHandle, void(*)(PatternHandle*)> pat(
    lg_create_pattern(),
    lg_destroy_pattern
  );
  result = lg_parse_pattern(pat.get(), "foo", nullptr, &errPtr);
  REQUIRE(result == 0);
  REQUIRE(errPtr);
  REQUIRE(0 == std::strcmp(errPtr->Message, "LG_KeyOptions parameter was null. Please pass a valid struct."));
  lg_free_error(errPtr);

  // recreate the errors, but pass in nullptr for the error handle
  result = lg_parse_pattern(nullptr, "foo", &keyOpts, nullptr);
  REQUIRE(result == 0);

  result = lg_parse_pattern(pat.get(), "foo", nullptr, nullptr);
  REQUIRE(result == 0);
}

TEST_CASE("testLgAddPatternWithNulls") {
  int result = 1;

  std::unique_ptr<PatternHandle, void(*)(PatternHandle*)> pat(
    lg_create_pattern(),
    lg_destroy_pattern
  );

  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0, 0),
    lg_destroy_fsm
  );

  LG_Error* err = nullptr;

  result = lg_add_pattern(nullptr, pat.get(), "UTF-8", 17, &err);
  REQUIRE(result < 0);
  REQUIRE(err);
  REQUIRE(std::string(err->Message) == "hFsm parameter was null. Use lg_create_fsm() to allocate.");
  lg_free_error(err);

  result = lg_add_pattern(fsm.get(), nullptr, "UTF-8", 17, &err);
  REQUIRE(result < 0);
  REQUIRE(err);
  REQUIRE(std::string(err->Message) == "hPattern parameter was null. Use lg_create_pattern() and lg_parse_pattern() first.");
  lg_free_error(err);

  result = lg_add_pattern(fsm.get(), pat.get(), nullptr, 17, &err);
  REQUIRE(result < 0);
  REQUIRE(err);
  REQUIRE(std::string(err->Message) == "encoding string pointer was null. Please specify a valid encoding.");
  lg_free_error(err);

  err = nullptr;
  LG_KeyOptions keyOpts;
  REQUIRE(0 < lg_parse_pattern(pat.get(), "foo", &keyOpts, &err));
  REQUIRE(!err);
  result = lg_add_pattern(fsm.get(), pat.get(), "UTF-39", 17, &err);
  REQUIRE(result < 0);
  REQUIRE(err);
  lg_free_error(err);
}

TEST_CASE("testLgAddPatternList") {
  const char pats[] =
    "foo\tUTF-8,UTF-16LE\t0\n"
    "bar\tISO-8859-11,UTF-16BE\t0\t1\n"
    "\\w+\tUTF-8\t0\t1\t1\n";
  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII", "UTF-8" };
  const size_t defEncsNum = std::extent_v<decltype(defEncs)>;
  const LG_KeyOptions defOpts{0, 0, 1};

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(patsNum, 0),
    lg_destroy_fsm
  );

  REQUIRE(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pats, "testLgAddPatternList",
    defEncs, defEncsNum, &defOpts, &err
  );

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};
  REQUIRE(!err);
}

TEST_CASE("testLgAddPatternListFixedString") {
  const char pats[] = "++\tASCII\t1\t0";
  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII" };
  const size_t defEncsNum = std::extent_v<decltype(defEncs)>;

  const LG_KeyOptions defOpts{0, 0, 1};

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(patsNum, 0),
    lg_destroy_fsm
  );

  REQUIRE(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pats, "testLgAddPatternListFixedString",
    defEncs, defEncsNum, &defOpts, &err
  );

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};
  REQUIRE(!err);
}

TEST_CASE("testLgAddPatternListCRLFHeck") {
  // Mixed line endings is obviously a stupid case
  // yet, let's remember Postel's Law...
  const std::string pats("foo\r\nbar\n\baz\rquux\r\n\r\n\nxyzzy");
  const char* defEncs[] = { "ASCII" };

  const LG_KeyOptions opts{0, 0, 1};

  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(5, 0),
    lg_destroy_fsm
  );

  REQUIRE(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pats.c_str(), "testLgAddPatternListCRLFHeck",
    defEncs, 1, &opts, &err
  );

  REQUIRE(!err);

  const char* exp_pats[] = { "foo", "bar", "\baz", "quux", "xyzzy" };

  REQUIRE(5u == lg_fsm_pattern_count(fsm.get()));

  for (int i = 0; i < 5; ++i) {
    const LG_PatternInfo* pi = lg_fsm_pattern_info(fsm.get(), i);
    REQUIRE(pi);
    REQUIRE(!std::strcmp(exp_pats[i], pi->Pattern));
  }

  const LG_ProgramOptions progOpts{0xFFFFFFFF};
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(
    lg_create_program(fsm.get(), &progOpts),
    lg_destroy_program
  );

  REQUIRE(prog);

  REQUIRE(5u == lg_prog_pattern_count(prog.get()));

  for (int i = 0; i < 5; ++i) {
    const LG_PatternInfo* pi = lg_prog_pattern_info(prog.get(), i);
    REQUIRE(pi);
    REQUIRE(!std::strcmp(exp_pats[i], pi->Pattern));
  }
}

TEST_CASE("testLgAddPatternListBadEncoding") {
  const char pats[] =
    "foo\tUTF-8,BOGUS\t0\t0\n"
    "x+\tASCII\n"
    "(ab)*c\tBOGUS\t0\t0\n";

  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII", "UTF-8" };
  const size_t defEncsNum = std::extent_v<decltype(defEncs)>;
  const LG_KeyOptions defOpts{0, 0, 1};

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(patsNum, 0),
    lg_destroy_fsm
  );

  REQUIRE(fsm);

// FIXME: finish this test
// FIXME: clean up err

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pats, "testLgAddPatternListBadEncoding",
    defEncs, defEncsNum, &defOpts, &err
  );

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};

  REQUIRE(err);
  REQUIRE(err->Message);
  REQUIRE(0 == err->Index);

  err = err->Next;
  REQUIRE(err);
  REQUIRE(err->Message);
  REQUIRE(2 == err->Index);

  err = err->Next;
  REQUIRE(!err);

/*
  for ( ; err; err = err->Next) {
    std::cerr << err->Index << ": " << err->Message << std::endl;
  }

*/
}

TEST_CASE("testLgAddPatternListCopyOnWritePatternMap") {
  const char pats1[] = "foo\tUTF-8\t0\t0\n";
  const size_t pats1Num = std::count(pats1, pats1 + std::strlen(pats1), '\n');

  const char* defEncs[] = { "UTF-8" };
  const size_t defEncsNum = std::extent_v<decltype(defEncs)>;
  const LG_KeyOptions defOpts{0, 0, 1};

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(pats1Num, 0),
    lg_destroy_fsm
  );

  REQUIRE(fsm);

  LG_Error* err = nullptr;
  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};

  // put some patterns into the fsm
  lg_add_pattern_list(
    fsm.get(), pats1, "whatever",
    defEncs, defEncsNum, &defOpts, &err
  );

  REQUIRE(!err);

  REQUIRE(lg_fsm_pattern_count(fsm.get()) == 1);

  // make a program
  const LG_ProgramOptions progOpts{0xFFFFFFFF};
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog1(
    lg_create_program(fsm.get(), &progOpts),
    lg_destroy_program
  );

  REQUIRE(prog1);

  // put more patterns into the fsm
  const char pats2[] = "bar\tUTF-8\t0\t0\n";

  lg_add_pattern_list(
    fsm.get(), pats2, "whatever",
    defEncs, defEncsNum, &defOpts, &err
  );

  REQUIRE(!err);

  REQUIRE(lg_fsm_pattern_count(fsm.get()) == 2);

  // the first program still has one pattern
  REQUIRE(lg_prog_pattern_count(prog1.get()) == 1);

  // make another program
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog2(
    lg_create_program(fsm.get(), &progOpts),
    lg_destroy_program
  );

  REQUIRE(prog2);

  // the second program has two patterns
  REQUIRE(lg_prog_pattern_count(prog2.get()) == 2);
  // the first program still has one pattern
  REQUIRE(lg_prog_pattern_count(prog1.get()) == 1);
}

void gotHit(void* ctx, const LG_SearchHit* const) {
  ++*static_cast<uint64_t*>(ctx);
}

TEST_CASE("testLgWriteProgramLgReadProgram") {
  const char pats[] =
    "foo\tUTF-8,UTF-16LE\t0\t0\n"
    "bar\tISO-8859-11,UTF-16BE\t0\t1\n";
  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII", "UTF-8" };
  const size_t defEncsNum = std::extent_v<decltype(defEncs)>;
  const LG_KeyOptions defOpts{0, 0, 0};

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(patsNum, 0),
    lg_destroy_fsm
  );

  REQUIRE(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pats, "testLgAddPatternList",
    defEncs, defEncsNum, &defOpts, &err
  );

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};
  REQUIRE(!err);

  const LG_ProgramOptions progOpts{0xFFFFFFFF};
  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog1(
    lg_create_program(fsm.get(), &progOpts),
    lg_destroy_program
  );

  REQUIRE(prog1);

  fsm.reset();

  const size_t psize = lg_program_size(prog1.get());
  std::unique_ptr<char[]> buf(new char[psize]);

  lg_write_program(prog1.get(), buf.get());

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog2(
    lg_read_program(buf.get(), psize),
    lg_destroy_program
  );

  REQUIRE(prog2);

  REQUIRE(
    lg_program_size(prog1.get()) ==
    lg_program_size(prog2.get())
  );

  const size_t p1count = lg_prog_pattern_count(prog1.get());
  const size_t p2count = lg_prog_pattern_count(prog2.get());
  REQUIRE(4 == p1count);
  REQUIRE(p1count == p2count);

  for (size_t i = 0; i < p1count; ++i) {
    REQUIRE(
      *lg_prog_pattern_info(prog1.get(), i) ==
      *lg_prog_pattern_info(prog2.get(), i)
    );
  }

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog3(
    lg_read_program(buf.get(), psize),
    lg_destroy_program
  );

  REQUIRE(prog3);

  REQUIRE(
    lg_program_size(prog1.get()) ==
    lg_program_size(prog3.get())
  );

  const size_t p3count = lg_prog_pattern_count(prog3.get());
  REQUIRE(p1count == p3count);

  for (size_t i = 0; i < p1count; ++i) {
    REQUIRE(
      *lg_prog_pattern_info(prog1.get(), i) ==
      *lg_prog_pattern_info(prog3.get(), i)
    );
  }

  const LG_ContextOptions ctxOpts = LG_ContextOptions();
  std::shared_ptr<ContextHandle> ctx(
    lg_create_context(prog2.get(), &ctxOpts),
    lg_destroy_context
  );

  const std::string s = "foo is totally bar";

  uint64_t numHits = 0;
  lg_search(ctx.get(), s.data(), s.data() + s.size(), 0, &numHits, gotHit);
  REQUIRE(numHits == 2);
}

TEST_CASE("parsePatternSlice") {
  const std::string patterns = "foo bar";
  LG_HPATTERN hPat = lg_create_pattern();
  LG_KeyOptions opts{0,0,0};
  LG_Error* err = nullptr;
  LG_HFSM fsm = lg_create_fsm(2, 0);
  REQUIRE(lg_parse_pattern_slice(hPat, &patterns[0], 3, &opts, &err) > 0);
  REQUIRE(lg_add_pattern(fsm, hPat, "ASCII", 0, &err) == 0);
  REQUIRE(std::string(lg_fsm_pattern_info(fsm, 0)->Pattern) == "foo");
  REQUIRE(lg_parse_pattern_slice(hPat, &patterns[4], 3, &opts, &err) > 0);
  REQUIRE(lg_add_pattern(fsm, hPat, "ASCII", 1, &err) == 1);
  REQUIRE(std::string(lg_fsm_pattern_info(fsm, 1)->Pattern) == "bar");
  lg_destroy_pattern(hPat);
  lg_destroy_fsm(fsm);
}
