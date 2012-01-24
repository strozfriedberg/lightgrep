// must include <fstream> before options.h, because of <iosfwd> usage
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <boost/tokenizer.hpp>

#include "options.h"
#include "utility.h"

bool readKeyFile(const std::string& keyFilePath, std::vector<Pattern>& keys) {
  std::ifstream keyFile(keyFilePath.c_str(), std::ios::in);
  keys.clear();
  if (keyFile) {
    while (keyFile) {
      char line[8192];
      keyFile.getline(line, 8192);
      std::string lineS(line);
      if (!lineS.empty()) {
        keys.push_back(Pattern(lineS));
        // std::cerr << "read " << lineS << std::endl;
      }
    }
    return !keys.empty();
  }
  else {
    std::cerr << "Could not open keywords file " <<  keyFilePath << std::endl;
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

std::vector< Pattern > Options::getKeys() const {
  std::vector< Pattern > ret;
  if (!SinglePattern.empty()) {
    ret.push_back(Pattern(SinglePattern));
  }
  else {
    readKeyFile(KeyFile, ret);
  }
  return ret;
}

void setBool(const std::string& s, bool& b) {
  int zeroCmp = s.compare("0"),
      oneCmp  = s.compare("1");
  if (0 == oneCmp) {
    b = true;
    return;
  }
  else if (0 == zeroCmp) {
    b = false;
    return;
  }
  // don't set if unrecognized
}

bool Options::parseLine(const std::string& line, std::vector<Pattern>& keys) const {
  typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

  if (!line.empty()) {
    const tokenizer tokens(line, boost::char_separator<char>("\t"));
    unsigned int num = 0;
    for (tokenizer::const_iterator it(tokens.begin()); it != tokens.end(); ++it) {
      ++num;
    }
    if (num > 0) {
      tokenizer::const_iterator curTok(tokens.begin());
      Pattern p(*curTok++, LiteralMode, CaseInsensitive, Encoding);
      if (4 == num) {
        setBool(*curTok++, p.FixedString);
        setBool(*curTok++, p.CaseInsensitive);
        const tokenizer encodings(*curTok, boost::char_separator<char>(","));
        if (curTok != encodings.end()) {
          for (tokenizer::const_iterator enc(encodings.begin()); enc != encodings.end(); ++enc) {
            p.Encoding = *enc;
            keys.push_back(p);
          }
          return true;
        }
      }
      keys.push_back(p);
      return true;
    }
  }
  return false;
}
