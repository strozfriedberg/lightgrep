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

#include "basic.h"
#include "container_out.h"

#include "catch.hpp"

#include <set>

#include <unicode/ucnv.h>

TEST_CASE("testICUStandards") {
  // check that ICU is defining exactly the standards we expect

  std::set<std::string> expected{
    "UTR22", "IANA", "MIME", "IBM", "WINDOWS", "JAVA", ""
  };

  std::set<std::string> actual;
  UErrorCode err = U_ZERO_ERROR;
  const uint32_t slen = ucnv_countStandards();
  for (uint32_t i = 0; i < slen; ++i) {
    actual.insert(ucnv_getStandard(i, &err));
    REQUIRE(!U_FAILURE(err));
  }

  REQUIRE(expected == actual);
}
