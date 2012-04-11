#include "concrete_encoders.h"
#include "encodings.h"
#include "unicode.h"

#include <iostream>
#include <stdexcept>

// FIXME: Maybe we should set endianness with a compile-time flag? This
// would let us do the fast thing (casting & assignment) for conversions
// from code points to UTF-16 and UTF-32, instead of assigning each byte
// individually, in the case where our architecture and the encoding are
// same-endian.
bool is_little_endian() {
  const uint16_t twobytes = 1;
  return reinterpret_cast<const byte*>(&twobytes)[0];
}

ICUEncoder::ICUEncoder(const char* name) {
  UErrorCode err = U_ZERO_ERROR;

  // ICU pivots through UTF-16 when transcoding; this converter is used
  // to turn our code points (single characters in UTF-32) into UTF-16.
  src_conv = ucnv_open(is_little_endian() ? "UTF-32LE" : "UTF-32BE", &err);
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Your ICU is missing UTF-32. Wat?");
  }

  // The pivot buffer used by ICU.
  pivot = new UChar[ucnv_getMaxCharSize(src_conv)];

  // The converter used to translate UTF-16 into our desired encoding.
  dst_conv = ucnv_open(name, &err);
  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Unrecognized encoding '" << name << "'");
  }

  // Tell ICU to halt conversion on code points unrepresentable in the
  // target encoding. 
  ucnv_setFromUCallBack(
    dst_conv,
    UCNV_FROM_U_CALLBACK_STOP,
    nullptr,
    nullptr,
    nullptr,
    &err
  );

  if (U_FAILURE(err)) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not set callback. Wat?");
  }
 
  max_bytes = ucnv_getMaxCharSize(dst_conv);
}

ICUEncoder::~ICUEncoder() {
  ucnv_close(src_conv);
  ucnv_close(dst_conv);
  delete[] pivot;
}

uint32 ICUEncoder::maxByteLength() const {
  return max_bytes;
}

uint32 ICUEncoder::write(int cp, byte buf[]) const {
  char* dst = reinterpret_cast<char*>(buf);
  const char* src = reinterpret_cast<const char*>(&cp);

  UChar* psrc = pivot;
  UChar* pdst = pivot;

  UErrorCode err = U_ZERO_ERROR;

  ucnv_convertEx(
    dst_conv,
    src_conv,
    &dst,
    dst + max_bytes,
    &src,
    src + sizeof(cp),
    pivot,
    &psrc,
    &pdst,
    pivot + sizeof(pivot),
    true,
    false,
    &err        
  );

  return U_FAILURE(err) ? 0 : dst - reinterpret_cast<char*>(buf);
}

uint32 ASCII::maxByteLength() const {
  return 1;
}

uint32 ASCII::write(int cp, byte buf[]) const {
  if (cp < 0) {
    return 0;
  }
  else if (cp < 256) {
    buf[0] = cp;
    return 1;
  }
  else {
    return 0;
  }
}

uint32 UTF8::maxByteLength() const {
  return 4;
}

uint32 UTF8::write(int cp, byte buf[]) const {
  if (cp < 0) {
    // too small
    return 0;
  }
  else if (cp < 0x80) {
    // one byte
    buf[0] = (byte) cp;
    return 1;
  }
  else if (cp < 0x800) {
    // two bytes
    buf[0] = 0xC0 | ((cp >> 6) & 0x1F);
    buf[1] = 0x80 | ( cp       & 0x3F);
    return 2;
  }
  else if (cp < 0xD800) {
    // three bytes
    buf[0] = 0xE0 | ((cp >> 12) & 0x0F);
    buf[1] = 0x80 | ((cp >>  6) & 0x3F);
    buf[2] = 0x80 | ( cp        & 0x3F);
    return 3;
  }
  else if (cp < 0xE000) {
    // UTF-16 surrogates, invalid
    return 0;
  }
  else if (cp < 0x10000) {
    // three bytes
    buf[0] = 0xE0 | ((cp >> 12) & 0x0F);
    buf[1] = 0x80 | ((cp >>  6) & 0x3F);
    buf[2] = 0x80 | ( cp        & 0x3F);
    return 3;
  }
  else if (cp < 0x110000) {
    // four bytes
    buf[0] = 0xF0 | ((cp >> 18) & 0x07);
    buf[1] = 0x80 | ((cp >> 12) & 0x3F);
    buf[2] = 0x80 | ((cp >>  6) & 0x3F);
    buf[3] = 0x80 | ( cp        & 0x3F);
    return 4;
  }
  else {
    // too large
    return 0;
  }
}

bool findTail(const ByteSet& bs0, const NFA& g, const Fragment& frag, NFA::VertexDescriptor& tail) {
  ByteSet bs1;
  for (const std::pair<NFA::VertexDescriptor,uint32>& i : frag.OutList) {
    bs1.reset();
    g[i.first].Trans->getBits(bs1);
    if (bs0 == bs1) {
      tail = i.first;
      return true;
    }
  }
  return false;
}

bool findHead(byte fb, const NFA& g, const Fragment& frag, NFA::VertexDescriptor& head) {
  ByteSet bs;
  for (NFA::VertexDescriptor i : frag.InList) {
    bs.reset();
    g[i].Trans->getBits(bs);
    if (bs[fb]) {
      head = i;
      return true;
    }
  }
  return false;
}

bool findMid(byte sb, const NFA& g, const NFA::VertexDescriptor head, NFA::VertexDescriptor& mid) {
  ByteSet bs;
  for (uint32 i = 0; i < g.outDegree(head); ++i) {
    mid = g.outVertex(head, i);
    bs.reset();
    g[mid].Trans->getBits(bs);
    if (bs[sb]) {
      return true; 
    }
  }
  return false;
}

bool matchToEnd(const byte* b, const byte* bend, byte elast, const NFA& g, const Fragment& frag, NFA::VertexDescriptor head) {
  NFA::VertexDescriptor tail;

  for ( ; b < bend - 1; ++b, head = tail) {
    if (!findMid(*b, g, head, tail)) {
      return false;
    }
  }

  ByteSet bs0;
  for (uint32 i = *b; i <= elast; ++i) {
    bs0.set(i);
  }

  ByteSet bs1;

  for (uint32 i = 0; i < g.outDegree(head); ++i) {
    tail = g.outVertex(head, i);
    bs1.reset();
    g[tail].Trans->getBits(bs1);
    if (bs0 == bs1) {
      return true;
    }
  }

  return false;
}

bool joinHead(const byte* b, const byte* bend, byte last, const NFA& g, const Fragment& frag, NFA::VertexDescriptor& head) {

  for (NFA::VertexDescriptor h : frag.InList) {
    for (uint32 i = 0; i < g.outDegree(h); ++i) {
      NFA::VertexDescriptor tail = g.outVertex(h, i);
      if (matchToEnd(b+1, bend, last, g, frag, tail)) {
        head = h;
        return true;
      }
    }
  }

  return false;
}

int UTF8::nextBreak(int cp) const {
  if (cp < 0x80) {
    return 0x7F;
  }
  else {
    byte b[4];
    uint32 len = write(cp, b);
    b[len-1] = 0xBF;
    int bcp;
    utf8_to_unicode(bcp, b, b+len);
    return bcp;
  }
}

void UTF8::write(const UnicodeSet& uset, NFA& g, Fragment& frag) const {
  frag.InList.clear();
  frag.OutList.clear();

  const UnicodeSet::const_iterator rend(uset.end());
  UnicodeSet::const_iterator r(uset.begin());

  NFA::VertexDescriptor head, tail;
  ByteSet bs;

  if (r == rend) {
    // this is an empty character class
    head = g.addVertex();
    g[head].Trans = g.TransFac->getCharClass(bs);
    frag.InList.push_back(head);
    frag.OutList.emplace_back(head, 0);
    return;
  }

  byte lb[4], nb[4];

  for ( ; r != rend; ++r) {
    int32 l = r->first, n;
    const int32 h = r->second - 1;

    // skip UTF-16 surrogate pairs; these can show up in \p{Age=n}
    if (0xD800 <= l && l <= 0xDFFF) {
      if (h <= 0xDFFF) {
        continue;
      }
      else {
        l = 0xE000;
      }
    }

    for ( ; l <= h; l = n + 1) {
      // find next break in the encoding after l 
      n = std::min(h, nextBreak(l));

      std::cerr << std::hex << l << ',' << n << " = "; 
 
      // [lb,nb] is a contiguous block in the encoding
      const uint32 llen = write(l, lb);
      const uint32 nlen = write(n, nb);

      std::copy(lb, lb+llen, std::ostream_iterator<uint32>(std::cerr, " "));
      std::cerr << "- ";
      std::copy(nb, nb+nlen, std::ostream_iterator<uint32>(std::cerr, " "));
      std::cerr << std::dec << std::endl;

      // merge [lb,nb] into the graph
      if (llen > 1) {
        // handle head
        if (!findHead(lb[0], g, frag, head)) {
          if (joinHead(lb, lb+llen, nb[nlen-1], g, frag, head)) {
            bs.reset();
            g[head].Trans->getBits(bs);
            bs.set(lb[0]);
            g[head].Trans = g.TransFac->getCharClass(bs);
          }
          else {
            head = g.addVertex();
            g[head].Trans = g.TransFac->getLit(lb[0]);
            frag.InList.push_back(head);
          }
        }

        // handle mids
        for (uint32 i = 1; i < llen-1; ++i) {
          if (!findMid(lb[i], g, head, tail)) {
            uint32 j = 0;
            for ( ; j < g.outDegree(head); ++j) {
              NFA::VertexDescriptor tail = g.outVertex(head, j);
              if (matchToEnd(lb+i+1, lb+llen, nb[nlen-1], g, frag, tail)) {
                bs.reset();
                g[tail].Trans->getBits(bs);
                bs.set(lb[i]);
                g[tail].Trans = g.TransFac->getCharClass(bs);
                break;
              }
            }
            if (j == g.outDegree(head)) {
              tail = g.addVertex();
              g[tail].Trans = g.TransFac->getLit(lb[i]);
              g.addEdge(head, tail);
            }
          }
          head = tail;
        }

        // handle tail
        bs.reset();

        if (g.outDegree(head) > 0) {
          tail = g.outVertex(head, 0);
          bs.reset();
          g[tail].Trans->getBits(bs);
          for (uint32 i = lb[llen-1]; i <= nb[nlen-1]; ++i) {
            bs.set(i);
          }
          g[tail].Trans = g.TransFac->getCharClass(bs);
        }
        else if (findTail(bs, g, frag, tail)) {
          uint32 i = 0;
          for ( ; i < g.outDegree(head); ++i) {
            if (g.outVertex(head, i) == tail) {
              break;
            }
          }
          if (i == g.outDegree(head)) {
            g.addEdge(head, tail);
          }
        }
        else {
          tail = g.addVertex();
          g[tail].Trans = g.TransFac->getRange(lb[llen-1], nb[nlen-1]);
          frag.OutList.emplace_back(tail, 0);
          g.addEdge(head, tail);
        }  
/*
        if (findTail(bs, g, frag, tail)) {
          uint32 i = 0;
          for ( ; i < g.outDegree(head); ++i) {
            if (g.outVertex(head, i) == tail) {
              break;
            }
          }
          if (i == g.outDegree(head)) {
            g.addEdge(head, tail);
          }
        }
        else if (g.outDegree(head) > 0) {
          tail = g.outVertex(head, 0);
          bs.reset();
          g[tail].Trans->getBits(bs);
          for (uint32 i = lb[llen-1]; i <= nb[nlen-1]; ++i) {
            bs.set(i);
          }
          g[tail].Trans = g.TransFac->getCharClass(bs);
        }
        else {
          tail = g.addVertex();
          g[tail].Trans = g.TransFac->getRange(lb[llen-1], nb[nlen-1]);
          frag.OutList.emplace_back(tail, 0);
          g.addEdge(head, tail);
        }
*/
      }
      else {
        bs.reset(); 

        if (frag.InList.empty()) {
          head = g.addVertex();
          frag.InList.push_back(head);
          frag.OutList.emplace_back(head, 0);
        }
        else {
          head = frag.InList.front();
          g[head].Trans->getBits(bs);
        }

        for (uint32 i = l; i <= n; ++i) {
          bs.set(i);
        }

        g[head].Trans = g.TransFac->getCharClass(bs);
      }
    }
  }

  g.Deterministic = false;
}

/*
void UTF8::write(const UnicodeSet& uset, NFA& g, Fragment& frag) const {
  frag.InList.clear();
  frag.OutList.clear();

  // UTF-8 is strongly monotone in code point order

  const UnicodeSet::const_iterator rend(uset.end());
  UnicodeSet::const_iterator r(uset.begin());

  NFA::VertexDescriptor head, tail;
  ByteSet bs;

  if (r == rend) {
    // this is an empty character class
    head = g.addVertex();
    g[head].Trans = g.TransFac->getCharClass(bs);
    frag.InList.push_back(head);
    frag.OutList.emplace_back(head, 0);
    return;
  }

  byte lb, ub;
  bool split = false;

  enum {
    NONE,
    ONE,
    TWO,
    RANGE,
    MANY
  } type = NONE;

  // handle 1-byte sequences
  if (r->first < 0x80) {
    head = g.addVertex();
    frag.InList.push_back(head);
    frag.OutList.emplace_back(head, 0);

    // collect the bytes 
    for ( ; r != rend; ++r) {
      lb = r->first;
      ub = std::min(r->second-1, 0x7Fu);

      if (lb > 0x7F) {
        break;
      }

      switch (ub - lb + 1) {
      case 1:
        switch (type) {
        case NONE:
          type = ONE;
          break;
        case ONE:
          type = TWO;
          break;
        case TWO:
        case RANGE:
          type = MANY;
        case MANY:
          break;
        }
        break;
      case 2:
        switch (type) {
        case NONE:
          type = TWO;
          break;
        case ONE:
        case TWO:
        case RANGE:
          type = MANY;
        case MANY:
          break;
        }
        break;
      default:
        switch (type) {
        case NONE:
          type = RANGE;
          break;
        case ONE:
        case TWO:
        case RANGE:
          type = MANY;
        case MANY:
          break;
        }
        break; 
      }

      for (uint32 i = lb; i <= ub; ++i) {
        bs[i] = true;
      }

      if (r->second > 0x80) {
        split = true;
        break;
      }
    }

    switch (type) {
    case ONE:
      g[head].Trans = g.TransFac->getLit(lb);
      break;
    case TWO:
      {
        for (uint32 i = 0; i < 256; ++i) {
          if (bs[i]) {
            for (uint32 j = i + 1; j < 256; ++j) {        
              if (bs[j]) {  
                g[head].Trans = g.TransFac->getEither(i, j);
                i = j = 256;  // i.e., break both loops
              }
            }
          }
        }
      }
      break;
    case RANGE:
      g[head].Trans = g.TransFac->getRange(lb, ub);
      break;
    case MANY:
      g[head].Trans = g.TransFac->getCharClass(bs);
      break;
    }
  }

  // handle 2-byte sequences

  if (split) {
    handleTwoByte(0x80, std::min(r->second-1, 0x7FFu), g, frag);
    split = false;
    ++r;
  }

  if (r == rend) {
    return;
  }

  if (r->first < 0x800) {
    for ( ; r != rend; ++r) {
      handleTwoByte(r->first, std::min(r->second-1, 0x7FFu), g, frag);

      if (r->second > 0x800) {
        split = true;
        break;
      }
    }
  }

  // handle 3-byte sequences

  if (split) {
    handleThreeByte(0x800, std::min(r->second-1, 0xFFFFu), g, frag);
    split = false;
    ++r;
  }

  if (r == rend) {
    return;
  }

  if (r->first < 0x10000) {
    for ( ; r != rend; ++r) {
      handleThreeByte(r->first, std::min(r->second-1, 0xFFFFu), g, frag);

      if (r->second > 0x10000) {
        split = true;
        break;
      }
    }
  }

  // handle 4-byte sequences

  if (split) {
    handleFourByte(0x10000, r->second-1, g, frag);
    ++r;
  }

  for ( ; r != rend; ++r) {
    handleFourByte(r->first, r->second-1, g, frag);
  }
*/

/*
  ByteSet bs;
  byte buf[4];

  for (UnicodeSet::range r : uset) {
    const uint32 l = r.first, h = r.second;
    for (uint32 cp = l; cp < h; ++cp) {
      const uint32 len = write(cp, buf);

      NFA::VertexDescriptor head = 0, tail;

      bs.reset();

      // find byte 0 in the in list
      for (NFA::VertexDescriptor i : frag.InList) {
        g[i].Trans->getBits(bs);
        if (bs[buf[0]]) {
          head = i;
          break;
        }
      }

      // add byte 0 to the in list if not there already
      if (!head) {
        head = g.addVertex();
        g[head].Trans = g.TransFac->getLit(buf[0]);
        frag.InList.push_back(head);
    
        if (len == 1) {
          // add trailing byte to out list
          frag.OutList.emplace_back(head, 0);
        }
      }

      tail = head;

      // move on to middle bytes, if any 
      for (uint32 i = 1; i < len - 1; ++i) {
        bs.reset();
        const uint32 odeg = g.outDegree(head);
        for (uint32 e = 0; e < odeg; ++e) {
          tail = g.outVertex(head, e);
          g[tail].Trans->getBits(bs);
          if (bs[buf[i]]) {
            goto NEXT;
          }
        }

        tail = g.addVertex();
        g.addEdge(head, tail);
        g[tail].Trans = g.TransFac->getLit(buf[i]);
        
NEXT:
        head = tail;
      }

      if (len > 1) {
        // handle trailing byte
        if (g.outDegree(head)) {
          tail = g.outVertex(head, 0);
          bs.reset();
          g[tail].Trans->getBits(bs);
          bs[buf[len-1]] = true;
          g[tail].Trans = g.TransFac->getCharClass(bs);
        }
        else {
          tail = g.addVertex();
          g.addEdge(head, tail);
          bs.reset();
          bs[buf[len-1]] = true;
          g[tail].Trans = g.TransFac->getCharClass(bs);

          // add trailing byte to out list
          frag.OutList.emplace_back(tail, 0);
        }
      }
    }
  }
*/

/*
  g.Deterministic = false;
}
*/


/*
EncodingsCodeMap getEncodingsMap() {
  EncodingsCodeMap map;
  const uint32 num = sizeof(LG_SUPPORTED_ENCODINGS) / sizeof(const char*);
  for (uint32 i = 0; i < num; ++i) {
    map.insert(std::make_pair(LG_SUPPORTED_ENCODINGS[i], i));
  }
  map.insert(std::make_pair("ANSI_X3.4-1968", LG_ENC_ASCII));
  map.insert(std::make_pair("ASCII", LG_ENC_ASCII));
  return map;
}
*/
