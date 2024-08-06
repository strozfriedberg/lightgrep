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

#include "rangeset.h"
#include "icuutil.h"

#include <unicode/uset.h>
#include <memory>

TEST_CASE("testUnicodeSetICUToLGDstEmpty") {
  std::unique_ptr<USet, void(*)(USet*)> src(uset_open(0x27, 0x3F), uset_close);
  UnicodeSet exp{{0x27,0x40}}, act;

  convUnicodeSet(act, src.get());
  REQUIRE(exp == act);
}

TEST_CASE("testUnicodeSetICUToLGDstNonEmpty") {
  // test that convUnicodeSet clears dst
  std::unique_ptr<USet, void(*)(USet*)> src(uset_open(0x27, 0x3F), uset_close);
  UnicodeSet exp{{0x27,0x40}}, act{0xBEEF};

  convUnicodeSet(act, src.get());
  REQUIRE(exp == act);
}

TEST_CASE("testUnicodeSetICUToLGDstNonEmptyAdd") {
  // test that addUnicodeSet does not clear dst
  std::unique_ptr<USet, void(*)(USet*)> src(uset_open(0x27, 0x3F), uset_close);
  UnicodeSet exp{{0x27,0x40},{0xBEEF, 0xBEF0}}, act{0xBEEF};

  addUnicodeSet(act, src.get());
  REQUIRE(exp == act);
}

TEST_CASE("testUnicodeSetLGToICUDstEmpty") {
  UnicodeSet src{{0x27,0x40}};
  std::unique_ptr<USet, void(*)(USet*)> exp(uset_open(0x27, 0x3F), uset_close);
  std::unique_ptr<USet, void(*)(USet*)> act(uset_openEmpty(), uset_close);

  convUnicodeSet(act.get(), src);
  REQUIRE(uset_equals(exp.get(), act.get()));
}

TEST_CASE("testUnicodeSetLGToICUDstNonEmpty") {
  // test that convUnicodeSet clears dst
  UnicodeSet src{{0x27,0x40}};
  std::unique_ptr<USet, void(*)(USet*)> exp(uset_open(0x27, 0x3F), uset_close);
  std::unique_ptr<USet, void(*)(USet*)> act(uset_open(0xBEEF, 0xBEEF), uset_close);

  convUnicodeSet(act.get(), src);
  REQUIRE(uset_equals(exp.get(), act.get()));
}
