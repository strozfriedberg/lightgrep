#include "dirreader.h"

#include "filerecord.h"
#include "hex.h"
#include "inputhandler.h"
#include "outputhandler.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

DirReader::DirReader(const std::string& path):
  Root(path),
  Input(),
  RecHasher(),
  Dirents(RecHasher)
{
}

void DirReader::setInputHandler(std::shared_ptr<InputHandler> in) {
  Input = in;
}

void DirReader::setOutputHandler(std::shared_ptr<OutputHandler> out) {
  Output = out;
}

bool DirReader::startReading() {
  try {
    for (const auto& de : fs::recursive_directory_iterator(Root)) {
      handleFile(de);
    }
  }
  catch (const fs::filesystem_error& e) {
    // TODO: Logger?
    std::cerr << "Error: " << e.path1() << ": " << e.what() << std::endl;
    return false;
  }

  while (!Dirents.empty()) {
    Output->outputDirent(Dirents.pop());
  }

  Input->flush();
  return true;
}

void DirReader::handleFile(const fs::directory_entry& de) {
  const auto& p = de.path().lexically_normal();

  const std::string filename = p.filename().generic_string();
  const std::string path = p.generic_string();
  const std::string parent_path = p.parent_path().generic_string();

  while (!Dirents.empty() && parent_path != Dirents.top()["path"]) {
    Output->outputDirent(Dirents.pop());
  }

  Dirents.push(filename, Conv.convertName(de));

  Input->push({
    Conv.convertMeta(de),
    de.is_directory() ?
      std::static_pointer_cast<BlockSequence>(std::make_shared<EmptyBlockSequence>()) :
      std::static_pointer_cast<BlockSequence>(std::make_shared<FileBlockSequence>(p.string()))
  });
}
