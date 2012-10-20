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

#include "hitwriter.h"

#include <scope/test.h>

SCOPE_TEST(hitWriterOutput) {
/*
  std::vector<std::pair<uint32, uint32 >> tbl;
  std::vector<std::string> keys,
                             encodings;
  std::stringstream stream;

  keys.push_back("whatever");
  encodings.push_back("ASCII");
  encodings.push_back("UCS-16");

  tbl.push_back(std::make_pair<uint32,uint32>(0, 0));
  tbl.push_back(std::make_pair<uint32,uint32>(0, 1));

  HitWriter writer(stream, tbl, keys, encodings);
  writer.collect(SearchHit(0, 10, 0));

  uint64 offset, end, keyIndex;
  std::string key, encoding;

  stream >> offset >> end >> keyIndex >> key >> encoding;
  SCOPE_ASSERT_EQUAL(0u, offset);
  SCOPE_ASSERT_EQUAL(10u, end);
  SCOPE_ASSERT_EQUAL(0u, keyIndex);
  SCOPE_ASSERT_EQUAL(std::string("whatever"), key);
  SCOPE_ASSERT_EQUAL(std::string("ASCII"), encoding);

  writer.collect(SearchHit(2, 22, 1));

  stream >> offset >> end >> keyIndex >> key >> encoding;
  SCOPE_ASSERT_EQUAL(2u, offset);
  SCOPE_ASSERT_EQUAL(22u, end);
  SCOPE_ASSERT_EQUAL(0u, keyIndex);
  SCOPE_ASSERT_EQUAL(std::string("whatever"), key);
  SCOPE_ASSERT_EQUAL(std::string("UCS-16"), encoding);
*/
}
