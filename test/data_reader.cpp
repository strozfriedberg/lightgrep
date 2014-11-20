#include <istream>

#include "data_reader.h"

bool readTestData(
  std::istream& in,
  std::vector<Pattern>& patterns,
  std::string& text,
  std::vector<SearchHit>& expected)
{
  uint32_t len, patcount;

  // read number of patterns
  in.read(reinterpret_cast<char*>(&patcount), sizeof(patcount));
  if (!in) {
    return false;
  }
  patterns.reserve(patcount);

  for (uint32_t i = 0; i < patcount; ++i) {
    // read pattern
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!in) return false;
    std::string pattern(len, '\0');
    in.read(&pattern[0], len);
    if (!in) return false;

    // read fixed
    bool fixed;
    in.read(reinterpret_cast<char*>(&fixed), 1);
    if (!in) return false;

    // read case-insensitive
    bool case_insensitive;
    in.read(reinterpret_cast<char*>(&case_insensitive), 1);
    if (!in) return false;

    // read encoding
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (!in) return false;
    std::string encoding(len, '\0');
    in.read(&encoding[0], len);
    if (!in) return false;

    patterns.emplace_back(pattern, fixed, case_insensitive, encoding);
  }

  // read text
  in.read(reinterpret_cast<char*>(&len), sizeof(len));
  if (!in) return false;
  text.assign(len, '\0');
  in.read(&text[0], len);
  if (!in) return false;

  // read hits
  in.read(reinterpret_cast<char*>(&len), sizeof(len));
  if (!in) return false;
  expected.resize(len);

  if (sizeof(SearchHit) == 24) {
    // data can be read in as-is, in one shot
    in.read(reinterpret_cast<char*>(&expected[0]), len*sizeof(SearchHit));
  }
  else {
    // we have to do it the hard way, one at a time, skipping the padding
    char buf[24];
    for (uint32_t i = 0; i < len; ++i) {
      in.read(buf, sizeof(buf));
      expected[i] = *reinterpret_cast<const SearchHit*>(buf);
    }
  }

  if (!in) return false;

  return true;
}
