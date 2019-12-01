#include "llama.h"

#include "cli.h"
#include "easyfut.h"
#include "filescheduler.h"
#include "outputbase.h"
#include "processor.h"
#include "reader.h"

#include <fstream>
#include <functional>
#include <iostream>
#include <streambuf>
#include <unordered_map>

#include <boost/filesystem.hpp>

#include <tsk/libtsk.h>

#include <hasher.h>


Llama::Llama()
    : CliParser(std::make_shared<Cli>()), Pool(),
      LgProg(nullptr, lg_destroy_program) {}

int Llama::run(int argc, const char *const argv[]) {
  Opts = CliParser->parse(argc, argv);

  if (Opts) {
    if ("help" == Opts->Command) {
      CliParser->printHelp(std::cout);
    } else if ("version" == Opts->Command) {
      CliParser->printVersion(std::cout);
    } else if ("search" == Opts->Command) {
      search();
    }
    return 0;
  }
  return 1;
}

void Llama::search() {
  if (init()) {
    std::cout << "Number of patterns: " << lg_pattern_count(LgProg.get())
              << std::endl;

    auto out = OutputBase::createTarWriter(Pool, Opts->TarPath);
    std::shared_ptr<Processor> protoProc(new Processor(Matcher, LgProg));
    auto scheduler =
        std::make_shared<FileScheduler>(Pool, protoProc, out, Opts);

    if (!Input->startReading(scheduler)) {
      std::cerr << "startReading returned an error" << std::endl;
    }
    Pool.join();
    std::cout << "All done" << std::endl;
  } else {
    std::cerr << "init returned false!" << std::endl;
  }
}

std::string readfile(const std::string &path) {
  std::ifstream f(path, std::ios::in);
  std::string str;
  f.seekg(0, std::ios::end);
  str.reserve(f.tellg());
  f.seekg(0, std::ios::beg);
  str.assign((std::istreambuf_iterator<char>(f)),
             std::istreambuf_iterator<char>());
  return str;
}

bool Llama::readpatterns(const std::vector<std::string> &keyFiles) {
  // std::cerr << "begin readpatterns" << std::endl;
  std::shared_ptr<FSMHandle> fsm(lg_create_fsm(100000), lg_destroy_fsm);
  LgProg = std::shared_ptr<ProgramHandle>(lg_create_program(100000),
                                          lg_destroy_program);

  const char *defaultEncodings[] = {"utf-8", "utf-16le"};
  LG_KeyOptions defaultKeyOpts{0, 0};
  LG_Error *errs = nullptr;

  for (auto keyf : keyFiles) {
    // std::cerr << "add patterns from " << keyf << std::endl;

    std::string patterns = readfile(keyf);
    // std::cerr << "Patterns are:\n" << patterns << std::endl;
    int result = lg_add_pattern_list(fsm.get(), LgProg.get(), patterns.c_str(),
                                     keyf.c_str(), defaultEncodings, 2,
                                     &defaultKeyOpts, &errs);
    if (result < 0) {
      throw std::runtime_error("lg_add_pattern_list errored on file " + keyf);
    }
  }
  // std::cerr << "compiling program" << std::endl;
  LG_ProgramOptions progOpts{1};
  if (lg_compile_program(fsm.get(), LgProg.get(), &progOpts)) {
    // std::cerr << "Number of patterns: " << lg_pattern_count(LgProg.get()) <<
    // std::endl; std::cerr << "Done with readpatterns" << std::endl;
    return true;
  } else {
    // add some error-handling someday
    return false;
  }
}

bool Llama::openInput(const std::string &input) {
  Input = InputReaderBase::createTSK(input);
  return bool(Input);
}

bool Llama::readMatchingSet(const std::string& matchSet) {
  std::string set = readfile(matchSet);
  LG_Error* errPtr = nullptr;
  Matcher = std::shared_ptr<SFHASH_FileMatcher>(sfhash_create_matcher(set.data(), set.data() + set.size(), &errPtr), sfhash_destroy_matcher);
  return true;
}

bool Llama::init() {
  if (Opts->KeyFiles.empty()) {
    return false;
  }
  auto readPats = make_future(
      Pool, [this]() { return readpatterns(this->Opts->KeyFiles); });
  auto readMatches = make_future(Pool, [this](){ return this->Opts->MatchSet.empty() || readMatchingSet(this->Opts->MatchSet); });
  auto open =
      make_future(Pool, [this]() { return openInput(this->Opts->Input); });

  return readPats.get() && readMatches.get() && open.get();
}
