/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

void collector(void* userData, const LG_SearchHit* const hit) {
  STest* stest = static_cast<STest*>(userData);
  stest->Hits.push_back(*static_cast<const SearchHit* const>(hit));
}

STest::STest(const std::vector<Pattern>& pats):
  Prog(nullptr, nullptr), Ctx(nullptr, nullptr)
{
  std::unique_ptr<PatternHandle,void(*)(PatternHandle*)> pat(
    lg_create_pattern(),
    lg_destroy_pattern
  );

  std::unique_ptr<PatternMapHandle,void(*)(PatternMapHandle*)> pmap(
    lg_create_pattern_map(pats.size()),
    lg_destroy_pattern_map
  );

  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(0),
    lg_destroy_fsm
  );

  LG_KeyOptions keyOpts;

  for (const Pattern& p : pats) {
    LG_Error* err = nullptr;

    keyOpts.CaseInsensitive = p.CaseInsensitive;
    keyOpts.FixedString = p.FixedString;

    lg_parse_pattern(pat.get(), p.Expression.c_str(), &keyOpts, &err);

    if (err) {
      lg_free_error(err);
      continue;
    }

    lg_add_pattern(fsm.get(), pmap.get(), pat.get(), p.Encoding.c_str(), &err);

    if (err) {
      lg_free_error(err);
    }
  }

  LG_ProgramOptions progOpts{1};

  Prog = std::unique_ptr<ProgramHandle,void(*)(ProgramHandle*)>(
    lg_create_program(fsm.get(), &progOpts),
    lg_destroy_program
  );

  if (Prog) {
    LG_ContextOptions ctxOpts;

    Ctx = std::unique_ptr<ContextHandle,void(*)(ContextHandle*)>(
      lg_create_context(Prog.get(), &ctxOpts),
      lg_destroy_context
    );
  }
}

// FIXME: lg_search wants const char*, why pass in const byte*?
void STest::search(const byte* begin, const byte* end, uint64 offset) {
  lg_search(Ctx.get(), reinterpret_cast<const char*>(begin), reinterpret_cast<const char*>(end), offset, this, collector);
  lg_closeout_search(Ctx.get(), this, collector);
}

void STest::startsWith(const byte* begin, const byte* end, uint64 offset) {
  lg_starts_with(Ctx.get(), reinterpret_cast<const char*>(begin), reinterpret_cast<const char*>(end), offset, this, collector);
}

bool STest::parsesButNotValid() const {
  return !Prog;
}
