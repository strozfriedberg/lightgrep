#include "concrete_encodings.h"
#include "encodings.h"

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
