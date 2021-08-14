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

#include "stest.h"

namespace {
  void collector(void* userData, const LG_SearchHit* const hit) {
    STest* stest = static_cast<STest*>(userData);

    stest->Hits.push_back(*static_cast<const SearchHit*>(hit));

    const LG_PatternInfo* info = lg_pattern_info(
      stest->Prog.get(), hit->KeywordIndex
    );

    // adjust the hit to reflect the user pattern index
    stest->Hits.back().KeywordIndex = info->UserIndex;
  }
}

void STest::init(const std::vector<Pattern>& pats) {
  std::unique_ptr<PatternHandle,void(*)(PatternHandle*)> pat(
    lg_create_pattern(),
    lg_destroy_pattern
  );

  Prog = std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)>(
    lg_create_program(pats.size()),
    lg_destroy_program
  );

  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  LG_KeyOptions keyOpts;

  size_t i = 0, numErrors = 0;
  for (const Pattern& p : pats) {
    LG_Error* err = nullptr;

    keyOpts = { p.FixedString, p.CaseInsensitive, p.UnicodeMode };
    lg_parse_pattern(pat.get(), p.Expression.c_str(), &keyOpts, &err);

    if (!err) {
      lg_add_pattern(
        fsm.get(), Prog.get(), pat.get(), p.Encoding.c_str(), i, &err
      );
    }

    if (err) {
      lg_free_error(err);
      ++numErrors;
    }

    ++i;
  }

  LG_ProgramOptions progOpts{0xFFFFFFFF};

  if (lg_compile_program(fsm.get(), Prog.get(), &progOpts)) {
    LG_ContextOptions ctxOpts;

    Ctx = std::unique_ptr<ContextHandle,void(*)(ContextHandle*)>(
      lg_create_context(Prog.get(), &ctxOpts),
      lg_destroy_context
    );
  }
  else {
    Prog.reset();
  }
}

void STest::search(const char* begin, const char* end, uint64_t offset) {
  RetVal = lg_search(Ctx.get(), begin, end, offset, this, collector);
  lg_closeout_search(Ctx.get(), this, collector);
}

void STest::startsWith(const char* begin, const char* end, uint64_t offset) {
  lg_starts_with(Ctx.get(), begin, end, offset, this, collector);
}

bool STest::parsesButNotValid() const {
  return !Prog;
}
