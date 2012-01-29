#pragma once

#include "basic.h"
#include <map>

class Encoding {
public:
  virtual uint32 maxByteLength() const = 0;
  virtual uint32 write(int ch, byte buf[]) const = 0;

  virtual ~Encoding() {}
};


typedef std::map< std::string, uint32 > EncodingsCodeMap;

EncodingsCodeMap getEncodingsMap();
