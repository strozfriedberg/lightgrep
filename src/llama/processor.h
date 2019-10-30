#pragma once

#include <memory>

#include "lightgrep/api.h"

struct FileRecord;
class OutputBase;

class Processor {
public:
  Processor(const std::shared_ptr<ProgramHandle>& prog);

  std::shared_ptr<Processor> clone() const;

  void process(const FileRecord& rec, OutputBase& out);

private:
  Processor(const Processor&); // noncopyable

  std::shared_ptr<ProgramHandle> LgProg; // shared

  std::shared_ptr<ContextHandle> Ctx; // not shared, could be unique_ptr
};
