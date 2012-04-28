#pragma once

#include "automata.h"
#include "compiler.h"
#include "encoder.h"
#include "nfabuilder.h"
#include "pattern.h"
#include "parsetree.h"

bool parse(const Pattern& pattern, ParseTree& tree);

bool parse(const std::string& text, bool litMode, bool caseInsensitive, ParseTree& tree);

class Parser {
public:
  Parser(uint32 sizeHint);

  ParseTree  Tree;
  NFABuilder Nfab;
  Compiler   Comp;
  NFAPtr     Fsm;

  typedef std::map<uint32, std::shared_ptr<Encoder>> EncodingMap;

  EncodingsCodeMap EncCodes;
  EncodingMap      Encoders;

  void addPattern(const Pattern& pattern, uint32 patIndex);
};
