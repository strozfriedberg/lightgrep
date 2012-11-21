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

#include <iostream>

#include "ascii.h"
#include "container_out.h"
#include "rotencoder.h"

SCOPE_TEST(testROTEncoderASCIIName) {
  ROTEncoder enc(13, ASCII());
  SCOPE_ASSERT_EQUAL("rot13|ASCII", enc.name());
}

SCOPE_TEST(testROTEncoderWriteSingleASCII) {
  ROTEncoder enc(13, ASCII());
  SCOPE_ASSERT_EQUAL(1u, enc.maxByteLength());

  byte buf[1];
  uint32 len;

  // too low
  SCOPE_ASSERT_EQUAL(0u, enc.write(-1, buf));

  // just right
  for (uint32 i = 0; i < 'A'; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(i, buf[0]);
  }

  for (uint32 i = 'A'; i < 'Z' + 1; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL('A'+(i-'A'+13)%26, buf[0]);
  }

  for (uint32 i = 'Z' + 1; i < 'a'; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(i, buf[0]);
  }

  for (uint32 i = 'a'; i < 'z' + 1; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL('a'+(i-'a'+13)%26, buf[0]);
  }

  for (uint32 i = 'z' + 1; i < 0x80; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(i, buf[0]);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0u, enc.write(0x80, buf));
}

SCOPE_TEST(testROTEncoderWriteSetASCII) {
/*
  ROTEncoder enc(13, ASCII());
 
  const std::vector<std::vector<ByteSet>> expected{
    {
      {
        0x41, 0x36, 0x13, 0x62, 0xA8, 0x21, 0x6E, 0xBB,
        0xF4, 0x16, 0xCC, 0x04, 0x7F, 0x64, 0xE8, 0x5D,
        0x1E, 0xF2, 0xCB, 0x2A, 0x74, 0xC5, 0x5E, 0x35,
        0xD2, 0x95, 0x47, 0x9E, 0x96, 0x2D, 0x9A, 0x88,
        0x4C, 0x7D, 0x84, 0x3F, 0xDB, 0xAC, 0x31, 0xB6,
        0x48, 0x5F, 0xF6, 0xC4, 0xD8, 0x39, 0x8B, 0xE7,
        0x23, 0x3B, 0x38, 0x8E, 0xC8, 0xC1, 0xDF, 0x25,
        0xB1, 0x20, 0xA5, 0x46, 0x60, 0x4E, 0x9C, 0xFB,
        0xAA, 0xD3, 0x56, 0x51, 0x45, 0x7C, 0x55, 0x00,
        0x07, 0xC9, 0x2B, 0x9D, 0x85, 0x9B, 0x09, 0xA0,
        0x8F, 0xAD, 0xB3, 0x0F, 0x63, 0xAB, 0x89, 0x4B,
        0xD7, 0xA7, 0x15, 0x5A, 0x71, 0x66, 0x42, 0xBF,
        0x26, 0x4A, 0x6B, 0x98, 0xFA, 0xEA, 0x77, 0x53,
        0xB2, 0x70, 0x05, 0x2C, 0xFD, 0x59, 0x3A, 0x86,
        0x7E, 0xCE, 0x06, 0xEB, 0x82, 0x78, 0x57, 0xC7,
        0x8D, 0x43, 0xAF, 0xB4, 0x1C, 0xD4, 0x5B, 0xCD
      }
    }
  };
 
  const UnicodeSet us{{0,0x80}};
  std::vector<std::vector<ByteSet>> actual;
  enc.write(us, actual);

  SCOPE_ASSERT_EQUAL(expected, actual);
*/
}
