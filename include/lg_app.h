#include <iosfwd>
#include <memory>
#include <tuple>

#include "handles.h"

class Options;

class NoName {
public:
  std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm;
  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog;
  std::unique_ptr<LG_Error, void(*)(LG_Error*)> err;

  NoName(
    std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm,
    std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog,
    std::unique_ptr<LG_Error, void(*)(LG_Error*)> err
    ) : fsm(std::move(fsm)), prog(std::move(prog)), err(std::move(err)) {};
};

NoName parsePatterns(const Options& opts);

void handleParseErrors(std::ostream& out, LG_Error* err, bool printFilename);

void writeProgram(const Options& opts, std::ostream& out);

