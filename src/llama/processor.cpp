#include "processor.h"

namespace {
  const LG_ContextOptions ctxOpts{0, 0};
}

Processor::Processor(const std::shared_ptr<ProgramHandle>& prog): Ctx(lg_create_context(prog.get(), &ctxOpts), lg_destroy_context) {}

void Processor::process(const FileRecord& rec, OutputBase& out) {

}
