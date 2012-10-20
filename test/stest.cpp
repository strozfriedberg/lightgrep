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

#include "utility.h"
#include "compiler.h"

void collector(void* userData, const LG_SearchHit* const hit) {
  STest* stest = static_cast<STest*>(userData);
  stest->Hits.push_back(*static_cast<const SearchHit* const>(hit));
}

STest::STest(const char* key) {
  std::initializer_list<const char*> keys = { key };
  init(keys);
}

STest::STest(std::initializer_list<const char*> keys) {
  init(keys);
}

STest::STest(const std::vector<Pattern>& patterns) {
  std::vector<Pattern> pats(patterns);
  init(pats);
}

void STest::init(std::vector<Pattern>& pats) {
  Fsm = createGraph(pats, true, true);
  if (Fsm) {
    Prog = Compiler::createProgram(*Fsm);
    Grep = VmInterface::create();
    Grep->init(Prog);
  }
}

void STest::search(const byte* begin, const byte* end, uint64 offset) {
  Grep->search(begin, end, offset, collector, this);
  Grep->closeOut(collector, this);
}

void STest::startsWith(const byte* begin, const byte* end, uint64 offset) {
  Grep->startsWith(begin, end, offset, collector, this);
}
