#include "processor.h"

namespace {
  const LG_ContextOptions ctxOpts{0, 0};
}

Processor::Processor(const std::shared_ptr<ProgramHandle>& prog):
  LgProg(prog),
  Ctx(lg_create_context(prog.get(), &ctxOpts), lg_destroy_context)
{}

std::shared_ptr<Processor> Processor::clone() const {
  return std::make_shared<Processor>(LgProg);
}

void Processor::process(const FileRecord& rec, OutputBase& out) {

}
