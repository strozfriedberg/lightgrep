#include <iosfwd>
#include <memory>
#include <tuple>

#include "handles.h"
#include "errors.h"

class Options;

class LgAppCollection {
public:
  std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm;
  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog;
  std::unique_ptr<LG_Error, void(*)(LG_Error*)> err;

  LgAppCollection(
    std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm,
    std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog,
    std::unique_ptr<LG_Error, void(*)(LG_Error*)> err
    ) : fsm(std::move(fsm)), prog(std::move(prog)), err(std::move(err)) {};
};

LgAppCollection parsePatterns(const Options& opts);

void handleParseErrors(std::ostream& out, LG_Error* err, bool printFilename);

void writeProgram(const Options& opts, std::ostream& out);

