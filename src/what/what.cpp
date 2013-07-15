/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013 Lightbox Technologies, Inc

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

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>

#include <unicode/uchar.h>

#include "parser.h"
#include "parsetree.h"
#include "rangeset.h"
#include "encoders/encoderfactory.h"

int main(int argc, char** argv) {
  // get the arguments
  if (argc != 3) {
    throw std::runtime_error("argc != 3");
  }

  const char* expr = argv[1];
  const char* encname = argv[2];

  // parse the character class
  ParseTree tree;
  if (!parse({expr, false, false}, tree)) {
    throw std::runtime_error("bad parse");
  }

  if (tree.Root->Type != ParseNode::REGEXP) {
    throw std::runtime_error("tree.Root->Type != ParseNode::REGEXP");
  }

  const ParseNode* cc = tree.Root->Child.Left;
  if (!cc) {
    throw std::runtime_error("!cc");
  }

  if (cc->Type != ParseNode::CHAR_CLASS) {
    throw std::runtime_error("cc->Type != ParseNode::CHAR_CLASS");
  }

  // get the encoders
  EncoderFactory efac;
  std::shared_ptr<Encoder> enc = efac.get(encname);
  if (!enc) {
    throw std::runtime_error("bad encoding");
  }

  std::shared_ptr<Encoder> utf8 = efac.get("UTF-8");
  if (!utf8) {
    throw std::runtime_error("wtf, no UTF-8");
  }

  byte rep[5];

  // NB: The code point with the longest name is U+FBF9, at 83 characters.
  // ICU gives us no way to querry this, sadly. Asshats.
  char cname[128];

  const UnicodeSet uset(cc->Set.CodePoints & enc->validCodePoints());
  for (const UnicodeSet::range& r : uset) {
    for (uint32_t i = r.first; i < r.second; ++i) {
      // get code point representation if printable
      switch (u_charType(i)) {
      case U_UNASSIGNED:
      case U_CONTROL_CHAR:
      case U_PRIVATE_USE_CHAR:
      case U_SURROGATE:
        rep[0] = '\0';
        break;

      default:
        {
          const uint32_t len = utf8->write(i, rep);
          if (len == 0) {
            throw std::runtime_error("wtf, invalid UTF-8");
          }
          rep[len] = '\0';
        }
      }

      // get code point name
      UErrorCode err = U_ZERO_ERROR;
      u_charName(i, U_EXTENDED_CHAR_NAME, &cname[0], sizeof(cname), &err);
      if (U_FAILURE(err)) {
        throw std::runtime_error(u_errorName(err));
      }

      // print it all
      std::cout << "U+" << std::hex << std::uppercase;
      if (i < 0x10000) {
        // BMB code points zero-fill to four digits
        std::cout << std::setw(4) << std::setfill('0');
      }
      std::cout << i << '\t' << rep << '\t' << cname << '\n';
    }
  }

  std::cout << std::endl;
  return EXIT_SUCCESS;
}
