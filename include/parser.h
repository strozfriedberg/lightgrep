#pragma once

#include "automata.h"
#include "nfaoptimizer.h"
#include "encoder.h"
#include "nfabuilder.h"
#include "pattern.h"
#include "parsetree.h"

#include <memory>
#include <string>

bool parse(const Pattern& pattern, ParseTree& tree);

bool parse(const std::string& text, bool litMode, bool caseInsensitive, ParseTree& tree);

class Parser {
public:
  Parser(uint32 sizeHint);

  ParseTree  Tree;
  NFABuilder Nfab;
  NFAOptimizer   Comp;
  NFAPtr     Fsm;

  std::map<std::string,std::shared_ptr<Encoder>> Encoders;

  void addPattern(const Pattern& pattern, uint32 patIndex);
};
