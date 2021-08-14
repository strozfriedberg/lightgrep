#include "recordhasher.h"

#include <string_view>

FieldHash RecordHasher::hashRun(const jsoncons::json& r) {
  auto h = Hasher.subhash();
  return Hasher.hash(
    r["offset"].as<uint64_t>(),
    r["addr"].as<uint64_t>(),
    r["len"].as<uint64_t>(),
    r["flags"].as<std::string_view>()
  );
}

FieldHash RecordHasher::hashStream(const jsoncons::json& r) {
  auto h = Hasher.subhash();
  return Hasher.hash(
    r["id"].as<uint64_t>(),
    r["type"].as<uint32_t>(),
    r["size"].as<uint64_t>(),
    r["name"].as<std::string_view>(),
    r["flags"].as<std::string_view>(),
    r["data_id"].as<std::string_view>()
  );
}

FieldHash RecordHasher::hashAttr(const jsoncons::json& r) {
  auto h = Hasher.subhash();
  Hasher.hash_em(
    r["nrd_initsize"].as<uint64_t>(),
    r["nrd_compsize"].as<uint64_t>(),
    r["nrd_skiplen"].as<uint64_t>(),
    r["nrd_allocsize"].as<uint64_t>(),
    r["rd_buf"].as<std::string_view>(),
    r["rd_buf_size"].as<uint64_t>(),
    hashStream(r["stream"]).hash
  );

  for (const auto& run: r["nrd_runs"].array_range()) {
    Hasher.hash_em(hashRun(run).hash);
  }

  return Hasher.get_hash();
}

FieldHash RecordHasher::hashInode(const jsoncons::json& r) {
  auto h = Hasher.subhash();
  Hasher.hash_em(
    r["addr"].as<uint64_t>(),
    r["flags"].as<std::string_view>(),
    r["type"].as<std::string_view>(),
    r["uid"].as<std::string_view>(),
    r["gid"].as<std::string_view>(),
    r["link"].as<std::string_view>(),
    r["nlink"].as<uint64_t>(),
    r["seq"].as<uint64_t>()
  );

/*
  for (const auto& ts: r["timestamps"].array_range()) {
    Hasher.hash_em(
      ts["name"].as<std::string_view>(),
      ts["ts"].as<std::string_view>()
    );
  }
*/

  for (const auto& attr: r["attrs"].array_range()) {
    Hasher.hash_em(hashAttr(attr).hash);
  }

  return Hasher.get_hash();
}

FieldHash RecordHasher::hashDirent(const jsoncons::json& r) {
  auto h = Hasher.subhash();
  Hasher.hash_em(
    r["type"].as<std::string_view>(),
    r["path"].as<std::string_view>()
  );

  for (const auto& s: r["streams"].array_range()) {
    Hasher.hash_em(s.as<std::string_view>());
  }

  for (const auto& c: r["children"].array_range()) {
    Hasher.hash_em(c.as<std::string_view>());
  }

  return Hasher.get_hash();
}
