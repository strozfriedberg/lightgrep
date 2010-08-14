#include "concrete_encodings.h"

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
