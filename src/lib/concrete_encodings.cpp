#include "concrete_encodings.h"
#include "encodings.h"

uint32 Ascii::maxByteLength() const {
  return 1u;
}

uint32 Ascii::write(int ch, byte buf[]) const {
  if (ch < 256) {
    buf[0] = ch;
    return 1;
  }
  return 0;
}



uint32 UCS16::maxByteLength() const {
  return 2u;
}

uint32 UCS16::write(int ch, byte buf[]) const {
  if (-1 < ch && ch < 65536) {
    *(unsigned short*)buf = ch;
    return 2;
  }
  return 0;
}

EncodingsCodeMap getEncodingsMap() {
  EncodingsCodeMap map;
  const uint32 num = sizeof(LG_SUPPORTED_ENCODINGS) / sizeof(const char*);
  for (uint32 i = 0; i < num; ++i) {
    map.insert(std::make_pair(std::string(LG_SUPPORTED_ENCODINGS[i]), i));
  }
  map.insert(std::make_pair("ANSI_X3.4-1968", LG_ENC_ASCII));
  map.insert(std::make_pair("ASCII", LG_ENC_ASCII));
  return map;
}
