#include "reader.h"

#include "tskreader.h"

std::shared_ptr<InputReaderBase>
InputReaderBase::createTSK(const std::string& imgName) {
  auto ret = std::make_shared<TSKReader>(imgName);
  if (!ret->open()) {
    throw std::runtime_error("Couldn't open image " + imgName);
  }
  return std::static_pointer_cast<InputReaderBase>(ret);
}

std::shared_ptr<InputReaderBase>
InputReaderBase::createDir(const std::string &) {
  return std::shared_ptr<InputReaderBase>();
}
