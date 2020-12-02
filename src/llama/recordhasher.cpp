#include "recordhasher.h"

#include <string_view>

FieldHash RecordHasher::hashRun(const jsoncons::json& r) {
  return Hasher.hash(
    r["offset"].as<uint64_t>(),
    r["addr"].as<uint64_t>(),
    r["len"].as<uint64_t>(),
    r["flags"].as<std::string_view>()
  );
}

FieldHash RecordHasher::hashStream(const jsoncons::json& r) {
  return Hasher.hash(
    r["id"].as<uint64_t>(),
    r["type"].as<uint32_t>(),
    r["size"].as<uint64_t>(),
    r["name"].as<std::string_view>(),
    '\0',
    r["flags"].as<std::string_view>(),
    '\0',
    r["data_id"].as<std::string_view>()
  );
}

FieldHash RecordHasher::hashAttr(const jsoncons::json& r) {
  const auto stream_hash = hashStream(r["stream"]);

  Hasher.reset();
  for (const auto& nrd: r["nrds"].array_range()) {
    Hasher.hash_em(hashRun(nrd).hash);
  }
  const auto nrds_hash = Hasher.get_hash();

  return Hasher.hash(
    r["init_size"].as<uint64_t>(),
    r["comp_size"].as<uint64_t>(),
    r["rd_buf"].as<std::string_view>(),
    '\0',
    r["rd_buf_size"].as<uint64_t>(),
    r["skip_len"].as<uint64_t>(),
    r["alloc_size"].as<uint64_t>(),
    stream_hash.hash,
    nrds_hash.hash
  );
}
