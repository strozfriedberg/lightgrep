#include "inputreader.h"

#include "dirreader.h"
#include "tskreader.h"
#include "tskwalkerimpl.h"
#include "tskwrapper.h"

std::shared_ptr<InputReader>
InputReader::createTSK(const std::string& imgName) {
  auto ret = std::make_shared<TskReader<TskWrapper, TskWalkerImpl>>(imgName);
  if (!ret->open()) {
    throw std::runtime_error("Couldn't open image " + imgName);
  }
  return std::static_pointer_cast<InputReader>(ret);
}

std::shared_ptr<InputReader>
InputReader::createDir(const std::string & dir) {
// TODO: maybe throw on failure?
  auto ret = std::make_shared<DirReader>(dir);
  return std::static_pointer_cast<InputReader>(ret);
}
