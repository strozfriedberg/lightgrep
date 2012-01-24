#pragma once

#include "pattern.h"
#include "parsenode.h"
#include "parsetree.h"
#include "nfabuilder.h"
#include "compiler.h"

bool parse(const std::string& text, bool litMode, ParseTree& tree);

class Parser {
public:
  Parser(uint32 sizeHint);

  ParseTree   Tree;
  NFABuilder  Nfab;
  Compiler    Comp;
  GraphPtr    Fsm;


  typedef std::map< uint32, boost::shared_ptr<Encoding> > EncodingMap;

  EncodingsCodeMap EncCodes;
  EncodingMap      Encoders;

  void addPattern(const Pattern& pattern, uint32 patIndex);
};
