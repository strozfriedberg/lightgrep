#include <scope/test.h>

#include <iostream>

#include "automata.h"
#include "concrete_encoders.h"
#include "fragment.h"

#include "utility.h"

SCOPE_TEST(testASCII) {
  ASCII enc;
  SCOPE_ASSERT_EQUAL(1u, enc.maxByteLength());

  byte buf[1];
  uint32 len;

  // too low
  SCOPE_ASSERT_EQUAL(0, enc.write(-1, buf));

  // just right
  for (uint32 i = 0; i < 256; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(i, buf[0]);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0, enc.write(256, buf));
}

SCOPE_TEST(testUTF8) {
  UTF8 enc;
  SCOPE_ASSERT_EQUAL(4, enc.maxByteLength());

  byte buf[4];
  uint32 len;
  int32 val;

  // too low
  SCOPE_ASSERT_EQUAL(0, enc.write(-1, buf));

  // one byte representations
  for (uint32 i = 0; i < 0x80; ++i) {
    len = enc.write(i, buf);
    SCOPE_ASSERT_EQUAL(1u, len);
    SCOPE_ASSERT_EQUAL(i, buf[0]);
  }

  // two-byte representations
  for (uint32 i = 0x80; i < 0x800; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x1F) << 6) | (buf[1] & 0x3F);
    SCOPE_ASSERT_EQUAL(2u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // low three-byte representations
  for (uint32 i = 0x800; i < 0xD800; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x0F) << 12) | ((buf[1] & 0x3F) << 6) | (buf[2] & 0x3F);
    SCOPE_ASSERT_EQUAL(3u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // UTF-16 surrogates, invalid
  for (uint32 i = 0xD800; i < 0xE000; ++i) {
    SCOPE_ASSERT_EQUAL(0, enc.write(i, buf));
  }

  // high three-byte representations
  for (uint32 i = 0xE000; i < 0x10000; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x0F) << 12) | ((buf[1] & 0x3F) << 6) | (buf[2] & 0x3F);
    SCOPE_ASSERT_EQUAL(3u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // four-byte representations
  for (uint32 i = 0x10000; i < 0x110000; ++i) {
    len = enc.write(i, buf);
    val = ((buf[0] & 0x07) << 18) | ((buf[1] & 0x3F) << 12) |
          ((buf[2] & 0x3F) <<  6) |  (buf[3] & 0x3F);
    SCOPE_ASSERT_EQUAL(4u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0, enc.write(0x110000, buf));
}

/*
SCOPE_TEST(testUTF8Graph0) {
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
//  eg[0].Trans = eg.TransFac->getLit(0xF1);
//  eg.addEdge(0, 1);
//  eg[1].Trans = eg.TransFac->getLit(0x80);
//  eg.addEdge(1, 2);
//  eg[2].Trans = eg.TransFac->getLit(0x80);
//  eg.addEdge(3, 4);
//  eg[3].Trans = eg.TransFac->getLit(0x80);
//
//  eg[4].Trans = eg.TransFac->getLit(0xF2);
//  eg.addEdge(4, 5);
//  eg[5].Trans = eg.TransFac->getLit(0x80);
//  eg.addEdge(5, 6);
//  eg[6].Trans = eg.TransFac->getLit(0x80);
//  eg.addEdge(6, 7);
//  eg[7].Trans = eg.TransFac->getLit(0x81);
//
//  Fragment efrag;
//  efrag.InList.push_back(0);
//  efrag.InList.push_back(4);
//  efrag.OutList.emplace_back(3, 0);
//  efrag.OutList.emplace_back(7, 0);
//
//  SCOPE_ASSERT_EQUAL(eg, ag);
//  SCOPE_ASSERT_EQUAL(efrag, afrag);
}

SCOPE_TEST(testUTF8Graph1) {
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

SCOPE_TEST(testUTF8Graph2) {
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

template <bool LE>
void utf16TestFixture(const UTF16<LE>& enc) {
  SCOPE_ASSERT_EQUAL(4u, enc.maxByteLength());

  byte buf[4];
  int32 val;
  uint32 len;

  // too low
  SCOPE_ASSERT_EQUAL(0, enc.write(-1, buf));

  // low direct representations
  for (uint32 i = 0; i < 0xD800; ++i) {
    len = enc.write(i, buf);
    val = buf[LE ? 1 : 0];
    val <<= 8;
    val += buf[LE ? 0 : 1];
    SCOPE_ASSERT_EQUAL(2u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // UTF-16 surrogates, invalid
  for (uint32 i = 0xD800; i < 0xE000; ++i) {
    SCOPE_ASSERT_EQUAL(0, enc.write(i, buf));
  }

  // high direct representations
  for (uint32 i = 0xE000; i < 0x10000; ++i) {
    len = enc.write(i, buf);
    val = buf[LE ? 1 : 0];
    val <<= 8;
    val += buf[LE ? 0 : 1];
    SCOPE_ASSERT_EQUAL(2u, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  uint32 lead, trail;

  // surrogate pair representations
  for (uint32 i = 0x10000; i < 0x110000; ++i) {
    len = enc.write(i, buf);

    lead = buf[LE ? 0 : 1] | (((uint16) buf[LE ? 1 : 0]) << 8);
    trail = buf[LE ? 2 : 3] | (((uint16) buf[LE ? 3 : 2]) << 8);

    val = (lead << 10) + trail + 0x10000 - (0xD800 << 10) - 0xDC00;

    SCOPE_ASSERT_EQUAL(4, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0, enc.write(0x110000, buf));
}

SCOPE_TEST(testUTF16LE) {
  UTF16LE enc;
  utf16TestFixture(enc);
}

SCOPE_TEST(testUTF16BE) {
  UTF16BE enc;
  utf16TestFixture(enc);
}

template <bool LE>
void utf32TestFixture(const UTF32<LE>& enc) {
  SCOPE_ASSERT_EQUAL(4u, enc.maxByteLength());

  byte buf[4];
  uint32 val;
  uint32 len;

  // too low
  SCOPE_ASSERT_EQUAL(0, enc.write(-1, buf));

  // low, valid
  for (uint32 i = 0; i < 0xD800; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32) buf[LE ? 1 : 2]) <<  8) |
          (((uint32) buf[LE ? 2 : 1]) << 16) |
          (((uint32) buf[LE ? 3 : 0]) << 24);

    SCOPE_ASSERT_EQUAL(4, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // UTF-16 surrogates, invalid
  for (uint32 i = 0xD800; i < 0xE000; ++i) {
    SCOPE_ASSERT_EQUAL(0, enc.write(i, buf));
  }

  // high, valid
  for (uint32 i = 0xE000; i < 0x110000; ++i) {
    len = enc.write(i, buf);

    val =            buf[LE ? 0 : 3]         |
          (((uint32) buf[LE ? 1 : 2]) <<  8) |
          (((uint32) buf[LE ? 2 : 1]) << 16) |
          (((uint32) buf[LE ? 3 : 0]) << 24);

    SCOPE_ASSERT_EQUAL(4, len);
    SCOPE_ASSERT_EQUAL(i, val);
  }

  // too high
  SCOPE_ASSERT_EQUAL(0, enc.write(0x110000, buf));
}

SCOPE_TEST(testUTF32LE) {
  UTF32LE enc;
  utf32TestFixture(enc);
}

SCOPE_TEST(testUTF32BE) {
  UTF32BE enc;
  utf32TestFixture(enc);
}
