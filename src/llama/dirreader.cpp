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
  Input()
{
}

void DirReader::setInputHandler(std::shared_ptr<InputHandler> in) {
  Input = in;
}

void DirReader::setOutputHandler(std::shared_ptr<OutputHandler> out) {
  Output = out;
}

void DirReader::finishDirent() {
  jsoncons::json rec{Dirents.pop()};

  const FieldHash fhash{RecHasher.hashDirent(rec)};
  std::string hash = hexEncode(&fhash.hash, sizeof(fhash.hash));

  if (!Dirents.empty()) {
    Dirents.top()["children"].push_back(std::move(hash));
  }

  Output->outputDirent(std::move(rec));
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
    finishDirent();
  }

  Input->flush();
  return true;
}

std::string ensureLeadingSlash(std::string s) {
  return s.empty() || s[0] != '/' ? "/" + s : s;
}

void DirReader::handleFile(const fs::directory_entry& de) {
  const auto& p = de.path().lexically_normal();

  const std::string filename = p.filename().generic_string();
  const std::string path = ensureLeadingSlash(p.generic_string());
  const std::string parent_path = ensureLeadingSlash(p.parent_path().generic_string());

  while (!Dirents.empty() && parent_path != Dirents.top()["path"]) {
    finishDirent();
  }

  Dirents.push(filename, Conv.convertName(de));

  Input->push({
    Conv.convertMeta(de),
    de.is_directory() ?
      std::static_pointer_cast<BlockSequence>(std::make_shared<EmptyBlockSequence>()) :
      std::static_pointer_cast<BlockSequence>(std::make_shared<FileBlockSequence>(p.string()))
  });
}
