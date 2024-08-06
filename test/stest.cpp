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

#include "stest.h"

namespace {
  void collector(void* userData, const LG_SearchHit* const hit) {
    STest* stest = static_cast<STest*>(userData);

    stest->Hits.push_back(*static_cast<const SearchHit*>(hit));

    const LG_PatternInfo* info = lg_prog_pattern_info(
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

  std::unique_ptr<FSMHandle,void(*)(FSMHandle*)> fsm(
    lg_create_fsm(pats.size(), 0),
    lg_destroy_fsm
  );

  LG_KeyOptions keyOpts;

  size_t i = 0;
  for (const Pattern& p : pats) {
    LG_Error* err = nullptr;

    keyOpts = { p.FixedString, p.CaseInsensitive, p.UnicodeMode };
    lg_parse_pattern(pat.get(), p.Expression.c_str(), &keyOpts, &err);

    if (!err) {
      lg_add_pattern(fsm.get(), pat.get(), p.Encoding.c_str(), i, &err);
    }

    if (err) {
      lg_free_error(err);
    }

    ++i;
  }

  LG_ProgramOptions progOpts{0xFFFFFFFF};

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
