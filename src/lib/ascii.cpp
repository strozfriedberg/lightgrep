#include "ascii.h"

uint32 ASCII::write(int cp, byte buf[]) const {
  if (cp < 0) {
    return 0;
  }
  else if (cp < 0x100) {
    buf[0] = cp;
    return 1;
  }
  else {
    return 0;
  }
}
