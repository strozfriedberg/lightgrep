/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <scope/test.h>

#include "lightgrep/api.h"

#include <algorithm>
#include <cstring>
#include <memory>

#include <iostream>

// #include "basic.h"

// TODO: complete this test?

/*
SCOPE_TEST(testDedupeOnDiffEncodings) {
  std::shared_ptr<ParserHandle> parser(lg_create_parser(0), lg_destroy_parser);
  LG_KeyOptions opts;
  opts.FixedString = 1;
  opts.CaseInsensitive = 0;
  LG_Error** err = nullptr;

  lg_add_keyword(parser.get(), "apple", 0, &opts, "ASCII", err);
  lg_add_keyword(parser.get(), "apple", 0, &opts, "UTF-8", err);

  LG_ProgramOptions progOpts;
  progOpts.Determinize = 1;

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

SCOPE_TEST(testLgAddPatternList) {
  const char pats[] =
    "foo\tUTF-8,UTF-16LE\t0\t0\n"
    "bar\tISO-8859-11,UTF-16BE\t0\t1\n";
  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII", "UTF-8" };
  const size_t defEncsNum = std::extent<decltype(defEncs)>::value;
  const LG_KeyOptions defOpts{0, 0};

  std::unique_ptr<PatternMapHandle,void(*)(PatternMapHandle*)> pmap(
    lg_create_pattern_map(patsNum),
    lg_destroy_pattern_map
  );

  SCOPE_ASSERT(pmap);

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  SCOPE_ASSERT(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pmap.get(), pats, "testLgAddPatternList",
    defEncs, defEncsNum, &defOpts, &err
  );

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};
  SCOPE_ASSERT(!err);
}

SCOPE_TEST(testLgAddPatternListFixedString) {
  const char pats[] = "++\tASCII\t1\t0";
  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII" };
  const size_t defEncsNum = std::extent<decltype(defEncs)>::value;

  const LG_KeyOptions defOpts{0, 0};

   std::unique_ptr<PatternMapHandle,void(*)(PatternMapHandle*)> pmap(
    lg_create_pattern_map(patsNum),
    lg_destroy_pattern_map
  );

  SCOPE_ASSERT(pmap);

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  SCOPE_ASSERT(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pmap.get(), pats, "testLgAddPatternListFixedString",
    defEncs, defEncsNum, &defOpts, &err
  );

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};
  SCOPE_ASSERT(!err);
}

SCOPE_TEST(testLgAddPatternListBadEncoding) {
  const char pats[] =
    "foo\tUTF-8,BOGUS\t0\t0\n"
    "x+\tASCII\n"
    "(ab)*c\tBOGUS\t0\t0\n";

  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII", "UTF-8" };
  const size_t defEncsNum = std::extent<decltype(defEncs)>::value;
  const LG_KeyOptions defOpts{0, 0};

  std::unique_ptr<PatternMapHandle,void(*)(PatternMapHandle*)> pmap(
    lg_create_pattern_map(patsNum),
    lg_destroy_pattern_map
  );

  SCOPE_ASSERT(pmap);

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  SCOPE_ASSERT(fsm);

// FIXME: finish this test
// FIXME: clean up err

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), pmap.get(), pats, "testLgAddPatternListBadEncoding",
    defEncs, defEncsNum, &defOpts, &err
  );

  std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};

  SCOPE_ASSERT(err);
  SCOPE_ASSERT_EQUAL(0, err->Index);

  err = err->Next;
  SCOPE_ASSERT(err);
  SCOPE_ASSERT_EQUAL(2, err->Index);

  err = err->Next;
  SCOPE_ASSERT(!err);

/*
  for ( ; err; err = err->Next) {
    std::cerr << err->Index << ": " << err->Message << std::endl;
  }

*/
}
