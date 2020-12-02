#pragma once

#include <memory>
#include <string>
#include <vector>

struct RunRecord {
  uint64_t offset;
  uint64_t addr;
  uint64_t len;
  std::string flags;   
};

struct StreamRecord {
  uint64_t id;
  uint32_t type;
  uint64_t size;
  std::string name; 
  std::string flags;
  std::string data_id;
};

struct AttrRecord {
  StreamRecord stream;
  uint64_t init_size;
  uint64_t comp_size; 
  std::unique_ptr<uint8_t[]> rd_buf;
  uint64_t rd_buf_size;
  uint64_t skip_len;
  uint64_t alloc_size;
  std::vector<RunRecord> nrds;
};

/*
struct InodeRecord {
  uint64_t addr;
  uint32_t uid;
  uint32_t gid;
  std::string mode;
  std::string flags;
  std::type string;
  std::vector<AttrRecord> attrs;
  std::vector<TimestampRecord> timestamps;
};
*/
