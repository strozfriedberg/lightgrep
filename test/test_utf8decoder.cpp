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

#include <scope/test.h>

#include <vector>

#include "decoders/bytesource.h"
#include "decoders/utf8decoder.h"

SCOPE_TEST(utf8DecoderName) {
  const byte buf[] = "x";
  UTF8Decoder d(std::unique_ptr<Decoder>(new ByteSource(buf, buf)));
  SCOPE_ASSERT_EQUAL("UTF-8", d.name());
}

SCOPE_TEST(utf8DecoderNext) {
  const byte buf[] = {
    'a', 'b', 'c', 0x80, 0x81, 0xF0, 0x9F, 0x92, 0xA9
  };
  // a    b    c  | invalid  | PILE_OF_POO

  UTF8Decoder d(std::unique_ptr<Decoder>(
    new ByteSource(buf, buf + sizeof(buf))
  ));

  const std::vector<std::pair<int32_t,const byte*>> exp{
    {'a', buf}, {'b', buf+1}, {'c', buf+2},
    {-0x81, buf+3}, {-0x82, buf+4},
    {0x1F4A9, buf+5},
    {Decoder::END, buf+9}
  };

  for (const std::pair<int32_t,const byte*>& cp : exp) {
    SCOPE_ASSERT_EQUAL(cp, d.next());
  }
}
