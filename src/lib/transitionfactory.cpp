#include "transitionfactory.h"

bool operator<(const ByteSet& a, const ByteSet& b) {
  // lexicographical ordering on ByteSets
  for (uint32 i = 0; i < 256; ++i) {
    if (a[i] < b[i]) {
      return true;
    }
  }

  return false;
}

bool TransitionFactory::Comp::operator()(const Transition* a, const Transition* b) {
  a_bytes.reset();
  b_bytes.reset();
  a->getBits(a_bytes);
  b->getBits(b_bytes);   
  return a_bytes < b_bytes;
}
