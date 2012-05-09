#include "encodings.h"

#include <algorithm>

int lg_get_encoding_id(const char* const name) {
  const LG_SUPPORTED_ENCODING* beg = LG_SUPPORTED_ENCODINGS;
  const LG_SUPPORTED_ENCODING* end =
    LG_SUPPORTED_ENCODINGS +
    sizeof(LG_SUPPORTED_ENCODINGS) / sizeof(LG_SUPPORTED_ENCODING);

  std::string ns(name);
  std::transform(ns.begin(), ns.end(), ns.begin(), tolower);

  const LG_SUPPORTED_ENCODING* ptr = std::find_if(
    beg,
    end,
    [&](const LG_SUPPORTED_ENCODING& e) -> bool {
      std::string es(e.name);
      std::transform(es.begin(), es.end(), es.begin(), tolower);
      return ns == es;
    }
  );

  return ptr == end ? -1 : ptr->idx;
}
