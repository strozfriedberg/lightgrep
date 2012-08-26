#pragma once

#include "basic.h"

#include "fwd_pointers.h"

class Compiler {
public:

  static ProgramPtr createProgram(const NFA& graph);


};
