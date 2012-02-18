#pragma once

#include "automata.h"
#include "compiler.h"
#include "nfabuilder.h"
#include "pattern.h"
#include "parsenode.h"
#include "parsetree.h"

bool parse(const std::string& text, bool litMode, ParseTree& tree);

class Parser {
public:
  Parser(uint32 sizeHint);

  ParseTree  Tree;
  NFABuilder Nfab;
  Compiler   Comp;
  NFAPtr     Fsm;

  typedef std::map<uint32, std::shared_ptr<Encoding>> EncodingMap;

  EncodingsCodeMap EncCodes;
  EncodingMap      Encoders;

  void addPattern(const Pattern& pattern, uint32 patIndex);
};
