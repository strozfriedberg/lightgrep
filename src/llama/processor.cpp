#include "processor.h"

#include <hasher/api.h>

#include "filerecord.h"
#include "outputhandler.h"

namespace {
const LG_ContextOptions ctxOpts{0, 0};
}

Processor::Processor(const std::shared_ptr<ProgramHandle>& prog):
   LgProg(prog),
   Ctx(prog.get() ? lg_create_context(prog.get(), &ctxOpts): nullptr, lg_destroy_context),
   Hasher(sfhash_create_hasher(SFHASH_MD5 | SFHASH_SHA_1 | SFHASH_SHA_2_256 | SFHASH_BLAKE3 | SFHASH_FUZZY | SFHASH_ENTROPY), sfhash_destroy_hasher)
{
}

std::shared_ptr<Processor> Processor::clone() const {
  return std::make_shared<Processor>(LgProg);
}

void Processor::process(FileRecord& rec, OutputHandler& out) {
  sfhash_reset_hasher(Hasher.get());
  sfhash_update_hasher(Hasher.get(), rec.fileBegin(), rec.fileEnd());
  sfhash_get_hashes(Hasher.get(), &rec.Hashes);
  out.outputInode(rec);
}
