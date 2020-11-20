#include "hex.h"

#include <hasher/api.h>

std::string hexEncode(const void* buf, size_t size) {
  std::string ret(2 * size, '\0');
  sfhash_hex(&ret[0], buf, size);
  return ret;
}

std::string hexEncode(const void* b, const void* e) {
  return hexEncode(b, static_cast<const uint8_t*>(e) -
                      static_cast<const uint8_t*>(b));
}
