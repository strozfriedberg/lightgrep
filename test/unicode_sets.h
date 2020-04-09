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

