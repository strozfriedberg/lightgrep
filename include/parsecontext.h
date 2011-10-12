#pragma once

#include "compiler.h"
#include "graph.h"
#include "nfabuilder.h"
#include "parsetree.h"

struct ParseContext {
  ParseTree   Tree;
  NFABuilder  Nfab;
  Compiler    Comp;
  GraphPtr    Fsm;

  ParseContext(unsigned int sizeHint): Fsm(new Graph(1, sizeHint)) {}
};
