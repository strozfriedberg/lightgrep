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

#include "decoders/bytesource.h"

TEST_CASE("byteSourceName") {
  const byte buf[] = "x";
  ByteSource bs(buf, buf);
  REQUIRE("" == bs.name());
}

TEST_CASE("byteSourceNext") {
  const byte buf[] = "abcdefghijklmnopqrstuvwxyz\n\t";
  ByteSource bs(buf, buf + sizeof(buf));
  for (size_t i = 0; i < sizeof(buf); ++i) {
    REQUIRE(std::make_pair((int32_t) buf[i], buf+i) == bs.next());
  }
  REQUIRE(std::make_pair(Decoder::END, buf+sizeof(buf)) == bs.next());
}
