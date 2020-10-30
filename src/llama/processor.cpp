#include "processor.h"

#include <hasher.h>

#include "filerecord.h"
#include "outputbase.h"

namespace {
const LG_ContextOptions ctxOpts{0, 0};
}

Processor::Processor(const std::shared_ptr<ProgramHandle> &prog):
   LgProg(prog),
   Ctx(prog.get() ? lg_create_context(prog.get(), &ctxOpts): nullptr, lg_destroy_context),
   Hasher(sfhash_create_hasher(MD5 | SHA1 | SHA256 | FUZZY | ENTROPY), sfhash_destroy_hasher)
{
}

std::shared_ptr<Processor> Processor::clone() const {
  return std::make_shared<Processor>(LgProg);
}

void Processor::process(FileRecord &rec, OutputBase &out) {
  sfhash_reset_hasher(Hasher.get());
  sfhash_update_hasher(Hasher.get(), rec.fileBegin(), rec.fileEnd());
  sfhash_get_hashes(Hasher.get(), &rec.Hashes);
  out.outputInode(rec);
}
