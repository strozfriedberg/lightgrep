#include "recordhasher.h"

#include "jsoncons_wrapper.h"
#include "records.h"

#include <cstring>
#include <ostream>
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

FieldHash RecordHasher::hash(const RunRecord& r) {
  return Hasher.hash(r.offset, r.addr, r.len, r.flags);
}

FieldHash RecordHasher::hash(const StreamRecord& r) {
  return Hasher.hash(r.id, r.type, r.size, '\0', r.name, '\0', r.flags);
}

FieldHash RecordHasher::hash(const AttrRecord& r) {
  const auto stream_hash = hash(r.stream);

  Hasher.reset();
  for (const auto& rr: r.nrds) {
    Hasher.hash_em(hash(rr).hash);
  }
  const auto nrds_hash = Hasher.get_hash();

  const auto rd_buf_hash = Hasher.hash(std::make_pair(r.rd_buf.get(), r.rd_buf.get() + r.rd_buf_size));

  return Hasher.hash(r.init_size, r.comp_size, rd_buf_hash.hash, r.rd_buf_size, r.skip_len, r.alloc_size, stream_hash.hash, nrds_hash.hash);
}

/*
std::string hash(const AttrRecord& r) {

  std::vector<uint8_t> buf;

  r.Doc["stream"]
  r.Doc["init_size"]
  r.Doc["comp_size"]
  r.Doc["rd_buf"]
  r.Doc["rd_buf_size"]
  r.Doc["skip_len"]
  r.Doc["alloc_size"]
  
  for (const auto& run : r.Doc["nrds"]) {
    buf.push_back(hash(run));
  }

}
*/
