#pragma once

#include <memory>

#include "lightgrep/api.h"

struct FileRecord;
class OutputBase;

class Processor {
public:
  Processor(const std::shared_ptr<ProgramHandle>& prog);

  void process(const FileRecord& rec, OutputBase& out);

private:
  std::shared_ptr<ContextHandle> Ctx;
};
