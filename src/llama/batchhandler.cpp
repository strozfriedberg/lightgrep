#include "batchhandler.h"

#include "filerecord.h"
#include "filescheduler.h"

BatchHandler::BatchHandler(std::shared_ptr<FileScheduler> sink):
  Sink(sink),
  CurBatch()
{
  resetCurBatch();
}

void BatchHandler::push(FileRecord&& f) {
  CurBatch->push_back(std::move(f));
  if (CurBatch->size() >= MaxCap) {
    flush();
  }
}

void BatchHandler::flush() {
  if (!CurBatch->empty()) {
    Sink->scheduleFileBatch(CurBatch);
    resetCurBatch();
  }
}

void BatchHandler::resetCurBatch() {
  CurBatch.reset(new std::vector<FileRecord>());
  CurBatch->reserve(MaxCap);
}