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
  std::unique_ptr<Errors> errors;

  LgAppCollection(
    std::unique_ptr<FSMHandle, void(*)(FSMHandle*)> fsm,
    std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)> prog,
    std::unique_ptr<Errors> errors
    ) : fsm(std::move(fsm)), prog(std::move(prog)), errors(std::move(errors)) {};

    LG_Error* getError() { return errors.get()->err; }
};

LgAppCollection parsePatterns(const Options& opts);

void writeProgram(const Options& opts, std::ostream& out);

