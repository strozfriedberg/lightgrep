#include "util.h"

#include <istream>

std::streampos stream_size(std::istream& in) {
  // this is seriously tedious compared to, oh, I don't know, file.size()
  const std::streampos cur = in.tellg();
  in.seekg(0, std::ios::end);
  const std::streampos end = in.tellg();
  in.seekg(cur, std::ios::beg);
  return end;
}
