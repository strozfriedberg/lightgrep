#include "filerecord.h"
#include "outputbase.h"
#include "pooloutputhandler.h"

void PoolOutputHandler::outputFile(const FileRecord& rec) {
  if (Closed) {
    // we might still have some records in FileRecBuf, but the 
    // threadpool has gone away and the MainStrand can no longer be
    // posted to, so just call into the function directly.
    Out->outputFile(rec);
  }
  else {
    boost::asio::post(MainStrand, [=](){ 
      Out->outputFile(rec);
    });
  }
}

void PoolOutputHandler::outputInode(const FileRecord& rec) {
  boost::asio::post(RecStrand, [=]() {
    InodesRecBuf.write(rec.str());
  });
}

void PoolOutputHandler::outputInodes(const std::shared_ptr<std::vector<FileRecord>>& batch) {
  boost::asio::post(RecStrand, [=]() {
    for (const auto& rec: *batch) {
      InodesRecBuf.write(rec.str());
      // FileRecBuf.get() << rec.Doc << '\n';
    }
  });
}

void PoolOutputHandler::outputSearchHit(const std::string&) {
}

void PoolOutputHandler::outputSearchHits(const std::vector<std::string>& batch) {
  for (const auto& hit: batch) {
    outputSearchHit(hit);
  }
}

void PoolOutputHandler::close() {
  Closed = true;
  if (InodesRecBuf.size()) {
    InodesRecBuf.flush();
  }
  Out->close();
}
