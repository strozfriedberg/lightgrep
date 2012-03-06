#include "concrete_encodings.h"
#include "encodings.h"

uint32 ASCII::maxByteLength() const {
  return 1;
}

uint32 ASCII::write(int cp, byte buf[]) const {
  if (cp < 256) {
    buf[0] = cp;
    return 1;
  }
  return 0;
}



uint32 UCS16::maxByteLength() const {
  return 2;
}

uint32 UCS16::write(int cp, byte buf[]) const {
  if (-1 < cp && cp < 65536) {
    *(unsigned short*)buf = cp;
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
