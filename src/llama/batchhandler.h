#include "inputhandler.h"

#include <memory>
#include <vector>

class FileScheduler;

class BatchHandler: public InputHandler {
public:
  BatchHandler(std::shared_ptr<FileScheduler> sink);

// FIXME: should the dtor flush?
  virtual ~BatchHandler() {}

// FIXME: would like a varargs emplace version too
  virtual void push(FileRecord&& f) override;

  virtual void flush() override;

private:
  void resetCurBatch();

  std::shared_ptr<FileScheduler> Sink;
// FIXME: why is CurBatch shared? could it just be moved?
  std::shared_ptr<std::vector<FileRecord>> CurBatch;

  const size_t MaxCap = 200;
};
