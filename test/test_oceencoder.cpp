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
#include "oceencoder.h"

SCOPE_TEST(testOCEEncoderASCIIName) {
  OCEEncoder<ASCII> enc;
  SCOPE_ASSERT_EQUAL("OCE(ASCII)", enc.name());
}

SCOPE_TEST(testOCEEncoderWriteSingleASCII) {
  OCEEncoder<ASCII> enc;
  SCOPE_ASSERT_EQUAL(1u, enc.maxByteLength());

  byte buf[1];
  uint32 len;

  // too low
  SCOPE_ASSERT_EQUAL(0u, enc.write(-1, buf));

  // just right
  for (uint32 i = 0; i < 0x80; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(OCEEncoder<ASCII>::OCE[i], buf[0]);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0u, enc.write(0x80, buf));
}

SCOPE_TEST(testOCEEncoderWriteSetASCII) {
  OCEEncoder<ASCII> enc;
 
  const std::vector<std::vector<ByteSet>> expected{
    {
      {
        0x47, 0xF1, 0xB4, 0xE6, 0x0B, 0x6A, 0x72, 0x48,
        0x85, 0x4E, 0x9E, 0xEB, 0xE2, 0xF8, 0x94, 0x53,
        0xE0, 0xBB, 0xA0, 0x02, 0xE8, 0x5A, 0x09, 0xAB,
        0xDB, 0xE3, 0xBA, 0xC6, 0x7C, 0xC3, 0x10, 0xDD,
        0x39, 0x05, 0x96, 0x30, 0xF5, 0x37, 0x60, 0x82,
        0x8C, 0xC9, 0x13, 0x4A, 0x6B, 0x1D, 0xF3, 0xFB,
        0x8F, 0x26, 0x97, 0xCA, 0x91, 0x17, 0x01, 0xC4,
        0x32, 0x2D, 0x6E, 0x31, 0x95, 0xFF, 0xD9, 0x23,
        0xD1, 0x00, 0x5E, 0x79, 0xDC, 0x44, 0x3B, 0x1A,
        0x28, 0xC5, 0x61, 0x57, 0x20, 0x90, 0x3D, 0x83,
        0xB9, 0x43, 0xBE, 0x67, 0xD2, 0x46, 0x42, 0x76,
        0xC0, 0x6D, 0x5B, 0x7E, 0xB2, 0x0F, 0x16, 0x29,
        0x3C, 0xA9, 0x03, 0x54, 0x0D, 0xDA, 0x5D, 0xDF,
        0xF6, 0xB7, 0xC7, 0x62, 0xCD, 0x8D, 0x06, 0xD3,
        0x69, 0x5C, 0x86, 0xD6, 0x14, 0xF7, 0xA5, 0x66,
        0x75, 0xAC, 0xB1, 0xE9, 0x45, 0x21, 0x70, 0x0C
      }
    }
  };
 
  const UnicodeSet us{{0,0x80}};
  std::vector<std::vector<ByteSet>> actual;
  enc.write(us, actual);

  SCOPE_ASSERT_EQUAL(expected, actual);
}
