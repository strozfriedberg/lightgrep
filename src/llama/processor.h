#pragma once

#include <memory>

#include "lightgrep/api.h"

struct SFHASH_Hasher;
struct FileRecord;
class OutputBase;

class Processor {
public:
  Processor(const std::shared_ptr<ProgramHandle> &prog);

  std::shared_ptr<Processor> clone() const;

  void process(FileRecord &rec, OutputBase &out);

private:
  Processor(const Processor &); // noncopyable

  std::shared_ptr<ProgramHandle> LgProg; // shared

  std::shared_ptr<ContextHandle> Ctx; // not shared, could be unique_ptr

  std::shared_ptr<SFHASH_Hasher> Hasher; // not shared, could be unique_ptr
};
