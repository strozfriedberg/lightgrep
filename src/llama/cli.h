#pragma once

#include <iosfwd>
#include <memory>

#include <boost/program_options.hpp>

#include "options.h"

class Cli {
public:
  Cli();

  std::shared_ptr<Options> parse(int argc, const char *const argv[]) const;

  void printVersion(std::ostream &out) const;
  void printHelp(std::ostream &out) const;

private:
  std::string figureOutCommand(const boost::program_options::variables_map& optsMap) const;
  Options::Codecs figureOutCodec() const;

  boost::program_options::options_description All;
  boost::program_options::positional_options_description PosOpts;

  std::shared_ptr<Options> Opts;
  std::string CodecSelect;
};
