#include "dirreader.h"

#include "filerecord.h"
#include "inputhandler.h"
#include "outputhandler.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

DirReader::DirReader(const std::string& path):
  Root(path),
  Input()
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
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
  }

  Input->flush();
  return true;
}

void DirReader::handleFile(const fs::directory_entry& de) {
  const auto& p = de.path();

  std::cerr << p << '\n';

  Input->push({
    Conv.convertMeta(de),
    de.is_directory() ?
      std::static_pointer_cast<BlockSequence>(std::make_shared<EmptyBlockSequence>()) :
      std::static_pointer_cast<BlockSequence>(std::make_shared<FileBlockSequence>(p.string()))
  });

  Output->outputDirent(Conv.convertName(de));
}
