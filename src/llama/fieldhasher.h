#pragma once

#include <cstring>
#include <iosfwd>
#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
//#include <vector>
#include <utility>

#include <hasher/api.h>

struct FieldHash {
  uint8_t hash[32];
};

bool operator==(const FieldHash& l, const FieldHash& r);

std::ostream& operator<<(std::ostream&, const FieldHash& r);

class FieldHasher {
public:
  FieldHasher() = default;

  FieldHasher(const FieldHasher&) = delete;

  FieldHasher(FieldHasher&&) = default;

  FieldHasher& operator=(const FieldHasher&) = delete;

  FieldHasher& operator=(FieldHasher&&) = default;

  template <typename...Args>
  FieldHash hash(Args&&... args) {
    reset();
    hash_em(std::forward<Args>(args)...);
    return get_hash();
  }

  void reset();

  FieldHash get_hash();

  template <typename... Args>
  FieldHasher& hash_em(Args&&... args) {
    (hash_it(std::forward<Args>(args)), ...);
    return *this;
  }

  FieldHasher& push();

  FieldHasher& pop();

  template <
    typename T,
    std::enable_if_t<std::is_arithmetic_v<T>, bool> = true
  >
  void hash_it(T t) {
    hash_it(&t, reinterpret_cast<const uint8_t*>(&t) + sizeof(t));
  }

  template <typename T, size_t N>
  void hash_it(const T(&a)[N]) {
    hash_it(std::begin(a), std::end(a));
  }

  void hash_it(const char* s);

  void hash_it(const std::string& s);

  void hash_it(const std::string_view& s);

/*
  template <
    typename T,
    std::enable_if_t<std::is_pointer_v<T>, bool> = true
  >
  void hash_it(const std::pair<T, T>& p) {
    hash_it(p.first, p.second);
  }
*/

  void hash_it_null_terminated(const void* beg, const void* end);

  void hash_it(const void* beg, const void* end);

/*
  template <typename C>
  auto hash_it(const C& c) -> decltype(std::cbegin(c), std::cend(c), void()) {
    for (const auto& e: c) {
      hash_it(e);
    }
  }
*/

private:
  std::unique_ptr<SFHASH_Hasher, void(*)(SFHASH_Hasher*)> Hasher{
    sfhash_create_hasher(SFHASH_BLAKE3), sfhash_destroy_hasher
  };
  SFHASH_HashValues Hashes;
};
