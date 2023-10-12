#include <iosfwd>
#include <memory>
#include <tuple>

#include "handles.h"

class Options;

std::tuple<
  std::unique_ptr<FSMHandle, void(*)(FSMHandle*)>,
  std::unique_ptr<ProgramHandle, void(*)(ProgramHandle*)>,
  std::unique_ptr<LG_Error, void(*)(LG_Error*)>
>
parsePatterns(const Options& opts);

void handleParseErrors(std::ostream& out, LG_Error* err, bool printFilename);

void writeProgram(const Options& opts, std::ostream& out);

