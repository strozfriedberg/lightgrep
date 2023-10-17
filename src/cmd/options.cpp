// must include <fstream> before options.h, because of <iosfwd> usage
#include <fstream>
#include "options.h"

#include <iostream>

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

std::vector<std::pair<std::string,std::string>> Options::getPatternLines() const {
  std::vector<std::pair<std::string,std::string>> ret;

  if (!CmdLinePatterns.empty()) {
    std::ostringstream os;

    // use patterns from the command line
    for (const std::string& p : CmdLinePatterns) {
      // pattern
      os << p << '\t';

      // encodings
      std::copy(
        Encodings.begin(), Encodings.end(),
        ostream_join_iterator<std::string>(os, ",")
      );

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

void Options::validateAndPopulateOptions(const po::variables_map &optsMap, std::vector<std::string> &pargs) {
// determine the source of our patterns

  validateAndPopulateKeyFiles(optsMap, pargs);

  CaseInsensitive = optsMap.count("ignore-case") > 0;
  LiteralMode = optsMap.count("fixed-strings") > 0;
  Binary = optsMap.count("binary") > 0;
  NoOutput = optsMap.count("no-output") > 0;
  Recursive = optsMap.count("recursive") > 0;
  MemoryMapped = optsMap.count("mmap") > 0;
  Verbose = optsMap.count("verbose") > 0;

  populateContextOptions(optsMap, pargs);

  // uppercase encoding names
  for (std::string& e : Encodings) {
    std::transform(e.begin(), e.end(), e.begin(), toupper);
  }

  if (optsMap.count("with-filename") && optsMap.count("no-filename")) {
    throw po::error("--with-filename and --no-filename are incompatible options");
  }

  if (Command == Options::SEARCH) {
    validateAndPopulateSearchOptions(optsMap, pargs);
  }
  else if (Command == Options::SAMPLES) {
    populateSampleOptions(optsMap, pargs);
  }

  // there should be no unused positional arguments now
  if (!pargs.empty()) {
    throw po::too_many_positional_options_error();
  }
}

void Options::validateAndPopulateKeyFiles(
  const boost::program_options::variables_map& optsMap, 
  std::vector<std::string>& pargs) {
    
  if (!optsMap["program-file"].empty()) {
    if (!optsMap["pattern"].empty() || !optsMap["keywords"].empty()) {
      throw po::error("--program-file is incompatible with --pattern and --keywords");
    }
  }
  else if (!optsMap["keywords"].empty() || !optsMap["pattern"].empty()) {
    // keywords from --keywords, not from the first positional argument
    if (!optsMap["keywords"].empty() && !optsMap["pattern"].empty()) {
      throw po::error("--pattern and --keywords are incompatible options");
    }
  }
  else {
    // keywords from parg
    if (pargs.empty()) {
      throw po::required_option("keywords");
    }

    KeyFiles.push_back(pargs.front());
    pargs.erase(pargs.begin());
  }
}

void Options::populateContextOptions(const boost::program_options::variables_map& optsMap, std::vector<std::string>&) {
  if (optsMap.count("context") > 0) {
      // "-C N" is equivalent to "-B N -A N"
      AfterContext = BeforeContext;
    }

  if (BeforeContext != -1 || AfterContext != -1) {
    // -C N, -B N, -A N imply --mmap
    MemoryMapped = true;
  }
}

void Options::validateAndPopulateSearchOptions(const boost::program_options::variables_map& optsMap, std::vector<std::string>& pargs) {
  // filename printing defaults off for single files, on for multiple files
  PrintPath = optsMap.count("with-filename") > 0;

  // determine the source of our input
  if (optsMap.count("arg-file") > 0) {
    PrintPath = optsMap.count("no-filename") == 0;
  }

  if (!pargs.empty()) {
    // input from pargs
    Inputs = pargs;
    pargs.clear();
    PrintPath = optsMap.count("no-filename") == 0;
  }
  else if (InputLists.empty()) {
    // input from stdin
    Inputs.push_back("-");
  }

  if (MemoryMapped && std::find(Inputs.begin(), Inputs.end(), "-") != Inputs.end()) {
    throw po::error("--mmap is incompatible with reading from stdin");
  }
}

void Options::populateSampleOptions(const boost::program_options::variables_map& optsMap, std::vector<std::string>& pargs) {
  SampleLimit =
        std::numeric_limits<std::set<std::string>::size_type>::max();
  LoopLimit = 1;

  if (!pargs.empty()) {
    SampleLimit = boost::lexical_cast<uint32_t>(pargs.front());
    pargs.erase(pargs.begin());

    if (!pargs.empty()) {
      LoopLimit = boost::lexical_cast<uint32_t>(pargs.front());
      pargs.erase(pargs.begin());
    }
  }
}
