#pragma once

#include <cstring>
#include <iosfwd>
#include <memory>
#include <string>
#include <type_traits>

#include <hasher/api.h>

struct FieldHash {
  uint8_t hash[32];
};

bool operator==(const FieldHash& l, const FieldHash& r);

std::ostream& operator<<(std::ostream&, const FieldHash& r);

class FieldHasher {
public:
  template <typename...Args>
  FieldHash hash(Args&&... args) {
    reset();
    hash_em(std::forward<Args>(args)...);
    return get_hash();
  }

  void reset(); 

  FieldHash get_hash();

  template <typename... Args>
  void hash_em(Args&&... args) {
    (hash_it(std::forward<Args>(args)), ...);
  }

  template <
    typename T,
    std::enable_if_t<std::is_arithmetic_v<T>, bool> = true
  >
  void hash_it(T t) {
    sfhash_update_hasher(Hasher.get(), &t, reinterpret_cast<const uint8_t*>(&t) + sizeof(t));
  }

  void hash_it(const char* s);

  void hash_it(const std::string& s);

private:
  std::unique_ptr<SFHASH_Hasher, void(*)(SFHASH_Hasher*)> Hasher{
    sfhash_create_hasher(SFHASH_BLAKE3), sfhash_destroy_hasher
  };
  SFHASH_HashValues Hashes;
};
