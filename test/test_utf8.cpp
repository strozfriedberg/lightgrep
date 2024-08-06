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

#include <catch2/catch_test_macros.hpp>

//#include "automata.h"
#include "container_out.h"
//#include "fragment.h"
//#include "utility.h"
#include "encoders/utf8.h"

TEST_CASE("testUTF8") {
  UTF8 enc;
  REQUIRE(4u == enc.maxByteLength());

  byte buf[4];
  uint32_t len;
  uint32_t val;

  // too low
  REQUIRE(0u == enc.write(-1, buf));

  // one byte representations
  for (uint32_t i = 0; i < 0x80; ++i) {
    len = enc.write(i, buf);
    REQUIRE(1u == len);
    REQUIRE(i == buf[0]);
  }

  // two-byte representations
  for (uint32_t i = 0x80; i < 0x800; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x1F) << 6) | (buf[1] & 0x3F);
    REQUIRE(2u == len);
    REQUIRE(i == val);
  }

  // low three-byte representations
  for (uint32_t i = 0x800; i < 0xD800; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x0F) << 12) | ((buf[1] & 0x3F) << 6) | (buf[2] & 0x3F);
    REQUIRE(3u == len);
    REQUIRE(i == val);
  }

  // UTF-16 surrogates, invalid
  for (uint32_t i = 0xD800; i < 0xE000; ++i) {
    REQUIRE(0u == enc.write(i, buf));
  }

  // high three-byte representations
  for (uint32_t i = 0xE000; i < 0x10000; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x0F) << 12) | ((buf[1] & 0x3F) << 6) | (buf[2] & 0x3F);
    REQUIRE(3u == len);
    REQUIRE(i == val);
  }

  // four-byte representations
  for (uint32_t i = 0x10000; i < 0x110000; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x07) << 18) | ((buf[1] & 0x3F) << 12) |
          ((buf[2] & 0x3F) <<  6) |  (buf[3] & 0x3F);
    REQUIRE(4u == len);
    REQUIRE(i == val);
  }

  // too high
  REQUIRE(0u == enc.write(0x110000, buf));
}

TEST_CASE("testUTF8Range0") {
  UTF8 enc;

  UnicodeSet us;
  us.set(0x40000);  // F1 80 80 80
  us.set(0x80001);  // F2 80 80 81

  const std::vector<std::vector<ByteSet>> e{
    { 0xF1, 0x80, 0x80, 0x80 },
    { 0xF2, 0x80, 0x80, 0x81 }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

TEST_CASE("testUTF8Range1") {
  UTF8 enc;

  UnicodeSet us;
  us.set(0x40000);  // F1 80 80 80
  us.set(0x80000);  // F2 80 80 80

  const std::vector<std::vector<ByteSet>> e{
    { {{0xF1, 0xF3}}, 0x80, 0x80, 0x80 }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

TEST_CASE("testUTF8Range2") {
  UTF8 enc;

  UnicodeSet us;
  us.set(0x400);    // D0 80
  us.set(0x1000);   // E1 80 80
  us.set(0x40000);  // F1 80 80 80

  const std::vector<std::vector<ByteSet>> e{
    { 0xD0, 0x80 },
    { 0xE1, 0x80, 0x80 },
    { 0xF1, 0x80, 0x80, 0x80 }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

TEST_CASE("testUTF8RangeFull") {
  UTF8 enc;

  UnicodeSet us{{0, 0x110000}};

  // all valid UTF-8 ranges
  const std::vector<std::vector<ByteSet>> e{
    { {{0x00, 0x80}} },
    { {{0xC2, 0xE0}}, {{0x80, 0xC0}} },
    {   0xE0,         {{0xA0, 0xC0}}, {{0x80, 0xC0}} },
    {   0xED,         {{0x80, 0xA0}}, {{0x80, 0xC0}} },
    { {{0xE1,0xED}, {0xEE,0xF0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
    {   0xF0,         {{0x90, 0xC0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
    {   0xF4,         {{0x80, 0x90}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} },
    { {{0xF1, 0xF4}}, {{0x80, 0xC0}}, {{0x80, 0xC0}}, {{0x80, 0xC0}} }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

TEST_CASE("testUTF8Disjoint") {
  UTF8 enc;

  UnicodeSet us;
  us.set(0x41);
  us.set(0x61);

  const std::vector<std::vector<ByteSet>> e{
    { {{0x41, 0x42}, {0x61, 0x62}} }
  };

  std::vector<std::vector<ByteSet>> a;
  enc.write(us, a);

  REQUIRE(e == a);
}

/*
TEST_CASE("testUTF8Graph0") {
  UTF8 enc;

  UnicodeSet us;
  us.set(0x40000);  // F1 80 80 80
  us.set(0x80001);  // F2 80 80 81

  NFA ag(1);
  Fragment afrag;
  enc.write(us, ag, afrag);

  for (NFA::VertexDescriptor v : afrag.InList) {
    ag.addEdge(0, v);
  }

  for (const auto& p : afrag.OutList) {
    ag[p.first].IsMatch = true;
  }

  writeGraphviz(std::cout, ag);

//  NFA eg(8);
//
//  eg[0].Trans = eg.TransFac->getByte(0xF1);
//  eg.addEdge(0, 1);
//  eg[1].Trans = eg.TransFac->getByte(0x80);
//  eg.addEdge(1, 2);
//  eg[2].Trans = eg.TransFac->getByte(0x80);
//  eg.addEdge(3, 4);
//  eg[3].Trans = eg.TransFac->getByte(0x80);
//
//  eg[4].Trans = eg.TransFac->getByte(0xF2);
//  eg.addEdge(4, 5);
//  eg[5].Trans = eg.TransFac->getByte(0x80);
//  eg.addEdge(5, 6);
//  eg[6].Trans = eg.TransFac->getByte(0x80);
//  eg.addEdge(6, 7);
//  eg[7].Trans = eg.TransFac->getByte(0x81);
//
//  Fragment efrag;
//  efrag.InList.push_back(0);
//  efrag.InList.push_back(4);
//  efrag.OutList.emplace_back(3, 0);
//  efrag.OutList.emplace_back(7, 0);
//
//  REQUIRE(eg == ag);
//  REQUIRE(efrag == afrag);
}

TEST_CASE("testUTF8Graph1") {
  UTF8 enc;

  UnicodeSet us;
  us.set(0x40000);  // F1 80 80 80
  us.set(0x80000);  // F2 80 80 80

  NFA ag(1);
  Fragment afrag;
  enc.write(us, ag, afrag);

  for (NFA::VertexDescriptor v : afrag.InList) {
    ag.addEdge(0, v);
  }

  for (const auto& p : afrag.OutList) {
    ag[p.first].IsMatch = true;
  }

  writeGraphviz(std::cout, ag);
}

TEST_CASE("testUTF8Graph2") {
  UTF8 enc;

  UnicodeSet us;
  us.set(0x400);    // D0 80
  us.set(0x1000);   // E1 80 80
  us.set(0x40000);  // F1 80 80 80

  NFA ag(1);
  Fragment afrag;
  enc.write(us, ag, afrag);

  for (NFA::VertexDescriptor v : afrag.InList) {
    ag.addEdge(0, v);
  }

  for (const auto& p : afrag.OutList) {
    ag[p.first].IsMatch = true;
  }

  writeGraphviz(std::cout, ag);
}
*/
