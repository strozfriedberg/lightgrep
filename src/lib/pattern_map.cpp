#include "pattern_map.h"

#include <algorithm>
#include <iterator>
#include <cstring>
#include <memory>
#include <numeric>

void PatternMap::clearPatterns() {
  if (!Shared) {
    for (LG_PatternInfo& pi: Patterns) {
      delete[] pi.Pattern;
      delete[] pi.EncodingChain;
    }
  }
  Patterns.clear();
  Shared = false;
}

void PatternMap::copyOther(const PatternMap& other) {
  Patterns.reserve(other.Patterns.size());
  for (const LG_PatternInfo& pi: other.Patterns) {
    addPattern(pi.Pattern, pi.EncodingChain, pi.UserIndex);
  }
}

PatternMap::PatternMap(const PatternMap& other): Patterns(), Shared(false) {
  copyOther(other);
}

PatternMap& PatternMap::operator=(const PatternMap& other) {
  clearPatterns();
  copyOther(other);
  return *this;
}

void PatternMap::addPattern(const char* pattern, const char* chain, uint64_t idx) {
  std::unique_ptr<char[]> patcopy(new char[std::strlen(pattern)+1]);
  std::strcpy(patcopy.get(), pattern);

  std::unique_ptr<char[]> chcopy(new char[std::strlen(chain)+1]);
  std::strcpy(chcopy.get(), chain);

  usePattern(patcopy.get(), chcopy.get(), idx);
  patcopy.release();
  chcopy.release();
}

size_t PatternMap::count() const {
  return Patterns.size();
}

void PatternMap::usePattern(const char* pattern, const char* chain, uint64_t idx) {
  Patterns.push_back({pattern, chain, idx});
}

std::vector<char> PatternMap::marshall() const {
  std::vector<char> buf(bufSize());
  char* i = buf.data();
  size_t slen;

  for (const LG_PatternInfo& pi: Patterns) {
    slen = std::strlen(pi.Pattern) + 1;
    std::memcpy(i, pi.Pattern, slen);
    i += slen;

    slen = std::strlen(pi.EncodingChain) + 1; 
    std::memcpy(i, pi.EncodingChain, slen);
    i += slen;

    std::memcpy(i, &pi.UserIndex, sizeof(pi.UserIndex));
    i += sizeof(pi.UserIndex); 
  }

  return buf; 
}

size_t PatternMap::bufSize() const {
  return std::accumulate(
    Patterns.begin(),
    Patterns.end(),
    0,
    [](size_t s, const LG_PatternInfo& pi) {
      return s + std::strlen(pi.Pattern) + 1
               + std::strlen(pi.EncodingChain) + 1
               + sizeof(pi.UserIndex); 
    }
  );
}

std::unique_ptr<PatternMap> PatternMap::unmarshall(const void* buf, size_t len) {
  std::unique_ptr<PatternMap> p(new PatternMap(0));
  p->Shared = true;

  const char* i = static_cast<const char*>(buf);
  const char* pat;
  const char* chain;
  const char* idx;
  
  const char* const end = i + len;
  
  while (i < end) {
    pat = i;
    chain = pat + std::strlen(pat) + 1;
    idx = chain + std::strlen(chain) + 1;

    p->usePattern(pat, chain, *reinterpret_cast<const uint64_t*>(idx));

    i = idx + sizeof(LG_PatternInfo::UserIndex); 
  }

  return p;
}

bool PatternMap::operator==(const PatternMap& rhs) const {
  return std::equal(Patterns.begin(), Patterns.end(), rhs.Patterns.begin());
}

bool operator==(const LG_PatternInfo& lhs, const LG_PatternInfo& rhs) {
  return lhs.UserIndex == rhs.UserIndex &&
         !std::strcmp(lhs.Pattern, rhs.Pattern) &&
         !std::strcmp(lhs.EncodingChain, rhs.EncodingChain);
}

std::ostream& operator<<(std::ostream& out, const PatternMap& p) {
  out << '[';
  std::copy(p.Patterns.begin(), p.Patterns.end(), std::ostream_iterator<LG_PatternInfo>(out, ", "));
  return out << ']';
}

std::ostream& operator<<(std::ostream& out, const LG_PatternInfo& pi) {
  return out << '['
             << pi.Pattern << ','
             << pi.EncodingChain << ','
             << pi.UserIndex
             << ']';
}
