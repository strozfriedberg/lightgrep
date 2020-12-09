#include "fieldhasher.h"

#include <cstring>
#include <ostream>

bool operator==(const FieldHash& l, const FieldHash& r) {
  return std::memcmp(l.hash, r.hash, sizeof(l.hash)) == 0;
}

std::ostream& operator<<(std::ostream& o, const FieldHash& h) {
  char hstr[sizeof(h.hash) * 2 + 1];
  sfhash_hex(&hstr[0], &h.hash, sizeof(h.hash));
  hstr[sizeof(h.hash) * 2] = '\0';
  return o << hstr;
}

void FieldHasher::reset() {
  sfhash_reset_hasher(Hasher.get());
}

FieldHash FieldHasher::get_hash() {
  sfhash_get_hashes(Hasher.get(), &Hashes);
  FieldHash h;
  std::memcpy(&h.hash, &Hashes.Blake3, sizeof(h.hash));
  return h;
}

void FieldHasher::hash_it(const char* s) {
  hash_it_null_terminated(s, s + std::strlen(s));
}

void FieldHasher::hash_it(const std::string& s) {
  hash_it_null_terminated(s.data(), s.data() + s.length());
}

void FieldHasher::hash_it(const std::string_view& s) {
  hash_it_null_terminated(s.data(), s.data() + s.length());
}

void FieldHasher::hash_it_null_terminated(const void* beg, const void* end) {
  hash_it(beg, end);
  hash_it('\0');
}

void FieldHasher::hash_it(const void* beg, const void* end) {
  sfhash_update_hasher(Hasher.get(), beg, end);
}
