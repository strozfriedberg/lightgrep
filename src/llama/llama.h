#pragma once

#include <boost/asio.hpp>

#include "cli.h"

#include "lightgrep/api.h"

class Llama {
public:
  Llama();

  int run(int argc, const char* const argv[]);

  void search();

  bool init();

private:
  bool readpatterns(const std::vector<std::string>& keyFiles);

  Cli CliParser;

  std::shared_ptr<Options> Opts;

  std::shared_ptr<ProgramHandle> LgProg;

  boost::asio::thread_pool Exec;
};
