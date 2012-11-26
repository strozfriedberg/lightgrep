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

#include <scope/test.h>

#include "encoders/ascii.h"

SCOPE_TEST(testASCII) {
  ASCII enc;
  SCOPE_ASSERT_EQUAL(1u, enc.maxByteLength());

  byte buf[1];
  uint32_t len;

  // too low
  SCOPE_ASSERT_EQUAL(0u, enc.write(-1, buf));

  // just right
  for (uint32_t i = 0; i < 0x80; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(i, buf[0]);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0u, enc.write(0x80, buf));
}
