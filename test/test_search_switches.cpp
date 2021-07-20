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

#include "catch.hpp"

#include <algorithm>
#include <cstring>

#include "stest.h"

TEST_CASE("ai_switches_Search") {
  STest fixture({
    {"(?i)x((?-i)x)x", false, false, true, "UTF-8"},
    {"(?i)k(?-i)k(?ai)k+", false, false, true, "UTF-8"},
    {"(?i)k(?-i)k(?i)k+", false, false, true, "UTF-8"}
  });
  fixture.search("XXX XxX xxx Kkkk Kk\xE2\x84\xAAK", 0);
  const std::vector<SearchHit> expected {
    SearchHit(4, 7, 0),
    SearchHit(8, 11, 0),
    SearchHit(12, 16, 2),
    SearchHit(12, 16, 1),
    SearchHit(17, 23, 2),
  };
  REQUIRE(expected == fixture.Hits);
}
