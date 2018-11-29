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

#include "pair_out.h"
#include <scope/test.h>

#include "rangeset.h"
#include "icuutil.h"

#include <unicode/uset.h>
#include <memory>

SCOPE_TEST(testUnicodeSetICUToLGDstEmpty) {
  std::unique_ptr<USet, void(*)(USet*)> src(uset_open(0x27, 0x3F), uset_close);
  UnicodeSet exp{{0x27,0x40}}, act;

  convUnicodeSet(act, src.get());
  SCOPE_ASSERT_EQUAL(exp, act);
}

SCOPE_TEST(testUnicodeSetICUToLGDstNonEmpty) {
  // test that convUnicodeSet clears dst
  std::unique_ptr<USet, void(*)(USet*)> src(uset_open(0x27, 0x3F), uset_close);
  UnicodeSet exp{{0x27,0x40}}, act{0xBEEF};

  convUnicodeSet(act, src.get());
  SCOPE_ASSERT_EQUAL(exp, act);
}

SCOPE_TEST(testUnicodeSetLGToICUDstEmpty) {
  UnicodeSet src{{0x27,0x40}};
  std::unique_ptr<USet, void(*)(USet*)> exp(uset_open(0x27, 0x3F), uset_close);
  std::unique_ptr<USet, void(*)(USet*)> act(uset_openEmpty(), uset_close);

  convUnicodeSet(act.get(), src);
  SCOPE_ASSERT(uset_equals(exp.get(), act.get()));
}

SCOPE_TEST(testUnicodeSetLGToICUDstNonEmpty) {
  // test that convUnicodeSet clears dst
  UnicodeSet src{{0x27,0x40}};
  std::unique_ptr<USet, void(*)(USet*)> exp(uset_open(0x27, 0x3F), uset_close);
  std::unique_ptr<USet, void(*)(USet*)> act(uset_open(0xBEEF, 0xBEEF), uset_close);

  convUnicodeSet(act.get(), src);
  SCOPE_ASSERT(uset_equals(exp.get(), act.get()));
}
