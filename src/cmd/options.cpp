#include <iostream>
// must include <fstream> before options.h, because of <iosfwd> usage
#include <fstream>

#include "options.h"
#include "ostream_join_iterator.h"
#include "util.h"

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

std::vector<std::pair<std::string,std::string>> Options::getKeyFiles() const {
  std::vector<std::pair<std::string,std::string>> ret;

  if (!CmdLinePatterns.empty()) {
    std::ostringstream os;

    // use patterns from the command line
    for (const std::string& p : CmdLinePatterns) {
      // pattern
      os << p << '\t';

      // encodings
      if (Encodings.empty()) {
        os << "ASCII";
      }
      else {
        std::copy(
          Encodings.begin(), Encodings.end(),
          ostream_join_iterator<std::string>(os, ",")
        );
      }

      os << '\t';

      // options
      os << static_cast<unsigned int>(LiteralMode) << '\t'
         << static_cast<unsigned int>(CaseInsensitive) << '\n';
    }

    ret.emplace_back("", os.str());
  }
  else {
    // use patterns from pattern files
    for (const std::string& kf : KeyFiles) {
      std::ifstream in(kf);
      if (in) {
// FIXME: handle I/O errors?

        // read the whole file
        const std::streampos size = stream_size(in);
        std::string buf(size, '\0');
        in.read(&buf[0], size);

        ret.emplace_back(kf, buf);
      }
      else {
        std::cerr << "Could not open pattern file " <<  kf << std::endl;
      }
    }
  }

  return ret;
}
