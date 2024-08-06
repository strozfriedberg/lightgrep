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


#pragma once

#include "parseutil.h"
#include "rangeset.h"

// horizontal space characters (matched by \h)
const UnicodeSet HSPACE({
  '\t',
  ' ',
  0xA0,   // NO-BREAK SPACE
  0x1680, // OGHAM SPACE MARK
  0x180E, // MONGOLIAN VOWEL SEPARATOR
  0x2000, // EN QUAD
  0x2001, // EM QUAD
  0x2002, // EN SPACE
  0x2003, // EM SPACE
  0x2004, // THREE-PER-EM SPACE
  0x2005, // FOUR-PER-EM SPACE
  0x2006, // SIX-PER-EM SPACE
  0x2007, // FIGURE SPACE
  0x2008, // PUNCTUATION SPACE
  0x2009, // THIN SPACE
  0x200A, // HAIR SPACE
  0x202F, // NARROW NO-BREAK SPACE
  0x205F, // MEDIUM MATHEMATICAL SPACE
  0x3000  // IDEOGRAPHIC SPACE
});

// vertical space characters (matched by \v)
const UnicodeSet VSPACE({
  '\n',
  '\v',    // NB: \v the ASCII escape != \v the character class
  '\f',
  '\r',
  0x85,   // NEXT LINE
  0x2028, // LINE SEPARATOR
  0x2029, // PARAGRAPH SEPARATOR
});

// space characters (matched by \s)
const UnicodeSet SPACE = HSPACE | VSPACE;

// NB: DIGIT and WORD grow as more blocks are added to Unicode. Hence we do
// not explicitly list them here, but rather query ICU for them for tests.
const UnicodeSet DIGIT(
  [](){ UnicodeSet s; setDigitClass(s, false); return s; }()
);

const UnicodeSet WORD(
  [](){ UnicodeSet s; setWordClass(s, false); return s; }()
);

