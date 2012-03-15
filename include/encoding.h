#pragma once

#include "basic.h"
#include "encodings.h"

#include <map>

class Encoding {
public:
  virtual uint32 maxByteLength() const = 0;
  virtual uint32 write(int cp, byte buf[]) const = 0;

  virtual ~Encoding() {}
};


typedef std::map<std::string, uint32> EncodingsCodeMap;

//EncodingsCodeMap getEncodingsMap();

static const EncodingsCodeMap ENCODINGS{
  { "US-ASCII",        0            },
  { "ISO_8859-1:1987", 1            },
  { "UTF-8",           2            },
  { "UTF-16",          3            },
  { "ASCII",           LG_ENC_ASCII },
  { "ANSI_X3.4-1968",  LG_ENC_ASCII }
};
