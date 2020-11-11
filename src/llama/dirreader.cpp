#include "dirreader.h"

#include "inputhandler.h"

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

bool DirReader::startReading() {
  try {
    for (const auto& de : fs::recursive_directory_iterator(Root)) {
      std::cout << de.path() << '\n';
    }
  }
  catch (const fs::filesystem_error& e) {
    // TODO: Logger?
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
  }

  return true;
}
