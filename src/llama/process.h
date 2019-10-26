#pragma once

#include "lightgrep/api.h"

class Processor {
public:
  Processor(std::shared_ptr<ProgramHandle> prog);

private:
  std::shared_ptr<ProgramHandle> LgProg;
};
