#pragma once

#include "boost_asio.h"
#include "outputhandler.h"
#include "recordbuffer.h"

class OutputChunk;
class OutputWriter;

class PoolOutputHandler: public OutputHandler {
public:
  PoolOutputHandler(boost::asio::thread_pool& pool, std::shared_ptr<OutputWriter> out):
    MainStrand(pool.get_executor()),
    RecStrand(pool.get_executor()),
    Out(out),
    ImageRecBuf("recs/image", 4 * 1024, [this](const OutputChunk& c) { Out->outputImage(c); }),
    InodesRecBuf("recs/inodes", 16 * 1024 * 1024, [this](const OutputChunk& c) { Out->outputInode(c); }),
    DirentsRecBuf("recs/dirents", 16 * 1024 * 1024, [this](const OutputChunk& c) { Out->outputDirent(c); }),
    Closed(false)
  {}

  virtual ~PoolOutputHandler() {
    close();
  }

  virtual void outputImage(const FileRecord& rec) override;

  virtual void outputDirent(const FileRecord& rec) override;

  virtual void outputInode(const FileRecord& rec) override;

  virtual void outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) override;

  virtual void outputSearchHit(const std::string&) override;

  virtual void outputSearchHits(const std::vector<std::string>& batch) override;

  virtual void close() override;

private:
  boost::asio::strand<boost::asio::thread_pool::executor_type> MainStrand,
                                                               RecStrand;

  std::shared_ptr<OutputWriter> Out;

  RecordBuffer ImageRecBuf;
  RecordBuffer InodesRecBuf;
  RecordBuffer DirentsRecBuf;

  bool Closed;
};
