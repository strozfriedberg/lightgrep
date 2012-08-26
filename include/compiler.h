#pragma once

#include "basic.h"

#include "program.h"
#include "automata.h"

class Compiler {
public:

  static ProgramPtr createProgram(const NFA& graph);


};
