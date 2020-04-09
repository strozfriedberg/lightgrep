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

#include "pattern_map.h"

// #include "basic.h"

// TODO: complete this test?

/*
SCOPE_TEST(testDedupeOnDiffEncodings) {
  std::shared_ptr<ParserHandle> parser(lg_create_parser(0), lg_destroy_parser);
  LG_KeyOptions opts;
  opts.FixedString = 1;
  opts.CaseInsensitive = 0;
  opts.UnicodeMode = 0;
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
    "foo\tUTF-8,UTF-16LE\t0\n"
    "bar\tISO-8859-11,UTF-16BE\t0\t1\n"
    "\\w+\tUTF-8\t0\t1\t1\n";
  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII", "UTF-8" };
  const size_t defEncsNum = std::extent<decltype(defEncs)>::value;
  const LG_KeyOptions defOpts{0, 0, 1};

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(
    lg_create_program(patsNum),
    lg_destroy_program
  );

  SCOPE_ASSERT(prog);

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  SCOPE_ASSERT(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), prog.get(), pats, "testLgAddPatternList",
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

  const LG_KeyOptions defOpts{0, 0, 1};

   std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(
    lg_create_program(patsNum),
    lg_destroy_program
  );

  SCOPE_ASSERT(prog);

  // FIXME: how to estimate NFA size here?
  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  SCOPE_ASSERT(fsm);

  LG_Error* err = nullptr;

  lg_add_pattern_list(
    fsm.get(), prog.get(), pats, "testLgAddPatternListFixedString",
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
  const LG_KeyOptions defOpts{0, 0, 1};

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog(
    lg_create_program(patsNum),
    lg_destroy_program
  );

  SCOPE_ASSERT(prog);

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
    fsm.get(), prog.get(), pats, "testLgAddPatternListBadEncoding",
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

SCOPE_TEST(testLgWriteProgramLgReadProgram) {
  const char pats[] =
    "foo\tUTF-8,UTF-16LE\t0\t0\n"
    "bar\tISO-8859-11,UTF-16BE\t0\t1\n";
  const size_t patsNum = std::count(pats, pats + std::strlen(pats), '\n');

  const char* defEncs[] = { "ASCII", "UTF-8" };
  const size_t defEncsNum = std::extent<decltype(defEncs)>::value;
  const LG_KeyOptions defOpts{0, 0, 0};

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog1(
    lg_create_program(patsNum),
    lg_destroy_program
  );

  SCOPE_ASSERT(prog1);

  {
    // FIXME: how to estimate NFA size here?
    std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
      lg_create_fsm(0),
      lg_destroy_fsm
    );

    SCOPE_ASSERT(fsm);

    LG_Error* err = nullptr;

    lg_add_pattern_list(
      fsm.get(), prog1.get(), pats, "testLgAddPatternList",
      defEncs, defEncsNum, &defOpts, &err
    );

    std::unique_ptr<LG_Error,void(*)(LG_Error*)> e{err, lg_free_error};
    SCOPE_ASSERT(!err);

    LG_ProgramOptions progOpts{1};
    int ret = lg_compile_program(fsm.get(), prog1.get(), &progOpts);
    SCOPE_ASSERT(ret);
  }

  const size_t psize = lg_program_size(prog1.get());
  std::unique_ptr<char[]> buf(new char[psize]);

  lg_write_program(prog1.get(), buf.get());

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog2(
    lg_read_program(buf.get(), psize),
    lg_destroy_program
  );

  SCOPE_ASSERT(prog2);

  SCOPE_ASSERT_EQUAL(
    lg_program_size(prog1.get()),
    lg_program_size(prog2.get())
  );

  const size_t p1count = lg_pattern_count(prog1.get());
  const size_t p2count = lg_pattern_count(prog2.get());
  SCOPE_ASSERT_EQUAL(p1count, p2count);

  for (size_t i = 0; i < p1count; ++i) {
    SCOPE_ASSERT_EQUAL(
      *lg_pattern_info(prog1.get(), i),
      *lg_pattern_info(prog2.get(), i)
    );
  }

  std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)> prog3(
    lg_read_program(buf.get(), psize),
    lg_destroy_program
  );

  SCOPE_ASSERT(prog3);

  SCOPE_ASSERT_EQUAL(
    lg_program_size(prog1.get()),
    lg_program_size(prog3.get())
  );

  const size_t p3count = lg_pattern_count(prog3.get());
  SCOPE_ASSERT_EQUAL(p1count, p3count);

  for (size_t i = 0; i < p1count; ++i) {
    SCOPE_ASSERT_EQUAL(
      *lg_pattern_info(prog1.get(), i),
      *lg_pattern_info(prog3.get(), i)
    );
  }
}
