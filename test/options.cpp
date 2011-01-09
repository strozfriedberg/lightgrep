// must include <fstrea> before options.h, because of <iosfwd> usage
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "options.h"
#include "utility.h"

bool readKeyFile(const std::string& keyFilePath, std::vector<std::string>& keys) {
  std::ifstream keyFile(keyFilePath.c_str(), std::ios::in);
  keys.clear();
  if (keyFile) {
    while (keyFile) {
      char line[8192];
      keyFile.getline(line, 8192);
      std::string lineS(line);
      if (!lineS.empty()) {
        keys.push_back(lineS);
        // std::cerr << "read " << lineS << std::endl;
      }
    }
    return !keys.empty();
  }
  else {
    std::cerr << "Could not open file" << std::endl;
    return false;
  }
}

uint32 Options::getEncoding() const {
  uint32 value = 0;
  if (Encoding == "ucs16") {
    value |= CP_UCS16;
  }
  else if (Encoding == "both") {
    value |= CP_UCS16;
    value |= CP_ASCII;
  }
  else if (Encoding == "ascii") {
    value |= CP_ASCII;
  }
  return value;
}

std::ostream& Options::openOutput() const {
  if (Output == "-") {
    return std::cout;
  }
  else {
    OutputFile.clear();
    OutputFile.open(Output.c_str(), std::ios::out);
    if (!OutputFile) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file " << Output);
    }
    return OutputFile;
  }
}

std::vector< std::string > Options::getKeys() const {
  std::vector< std::string > ret;
  if (!Pattern.empty()) {
    ret.push_back(Pattern);
  }
  else {
    readKeyFile(KeyFile, ret);
  }
  return ret;
}
