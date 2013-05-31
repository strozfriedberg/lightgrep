// must include <fstream> before options.h, because of <iosfwd> usage
#include <iostream>
#include <fstream>
#include <stdexcept>

#include <boost/tokenizer.hpp>

#include "options.h"

bool Options::readKeyFile(const std::string& keyFilePath, std::vector<Key>& keys) const {
  std::ifstream keyFile(keyFilePath.c_str(), std::ios::in);
  if (keyFile) {
    char line[8192];
    for (uint32_t lineno = 0; keyFile; ++lineno) {
      keyFile.getline(line, sizeof(line));
      parseLine(line, lineno, keys);
    }
    return !keys.empty();
  }
  else {
    std::cerr << "Could not open keywords file " <<  keyFilePath << std::endl;
    return false;
  }
}

std::ostream& Options::openOutput() const {
  if (Output == "-") {
    return std::cout;
  }
  else {
    OutputFile.clear();
    std::ios_base::openmode mode = std::ios::out;
    if (Binary) {
      mode |= std::ios::binary;
    }
    OutputFile.open(Output.c_str(), mode);
    if (!OutputFile) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not open output file " << Output);
    }
    return OutputFile;
  }
}

std::vector<Key> Options::getKeys() const {
  std::vector<Key> ret;
  if (!CmdLinePatterns.empty()) {
    uint32_t lineno = 0;
    for (const std::string& p : CmdLinePatterns) {
      parseLine(p, lineno++, ret);
    }
  }
  else {
    for (const std::string& kf : KeyFiles) {
      readKeyFile(kf, ret);
    }
  }
  return ret;
}

void setBool(const std::string& s, bool& b) {
  if (0 == s.compare("1")) {
    b = true;
  }
  else if (0 == s.compare("0")) {
    b = false;
  }
  // don't set if unrecognized
}

bool Options::parseLine(const std::string& line, uint32_t lineno, std::vector<Key>& keys) const {
  typedef boost::char_separator<char> char_separator;
  typedef boost::tokenizer<char_separator> tokenizer;

  if (!line.empty()) {
    const tokenizer tokens(line, char_separator("\t"));
    tokenizer::const_iterator curTok(tokens.begin());
    const tokenizer::const_iterator endTok(tokens.end());
    if (curTok != endTok) {
      Key p(*curTok, LiteralMode, CaseInsensitive);
      p.UserIndex = lineno;

      if (++curTok == endTok) {
        // encoding names are in Encodings
        if (Encodings.empty()) {
          return false;
        }

        for (const std::string& enc : Encodings) {
          p.Encoding = { enc };
          keys.push_back(p);
        }
      }
      else {
        // encoding names are at the end of the line
        setBool(*curTok, p.FixedString);
        if (++curTok == endTok) {
          return false;
        }
        setBool(*curTok, p.CaseInsensitive);

        if (++curTok == endTok) {
          return false;
        }

        const tokenizer encList(*curTok, char_separator(","));
        if (encList.begin() == encList.end()) {
          return false;
        }

        for (const std::string& enc : encList) {
          p.Encoding = { enc };
          keys.push_back(p);
        }
      }

      return true;
    }
  }
  return false;
}
