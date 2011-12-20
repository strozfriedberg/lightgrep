#pragma once

#include "parsenode.h"
#include "parsetree.h"
#include "nfabuilder.h"
#include "compiler.h"

bool parse(const std::string& text, bool litMode, ParseTree& tree);

class Parser {
public:
  Parser(uint32 sizeHint): Fsm(new Graph(1, sizeHint)) {}

  ParseTree   Tree;
  NFABuilder  Nfab;
  Compiler    Comp;
  GraphPtr    Fsm;

  void addPattern(const std::string& pattern, uint32 patIndex, const LG_KeyOptions& keyOpts);
};
