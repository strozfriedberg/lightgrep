#include "parser.h"
#include "encodings.h"
#include "encoding.h"
#include "concrete_encodings.h"
#include "rewriter.h"


Parser::EncodingMap createEncodingMap() {
  Parser::EncodingMap map;
  map[LG_ENC_ASCII].reset(new Ascii);
  map[LG_ENC_UTF_16].reset(new UCS16);
  map[LG_ENC_UTF_8].reset(new Ascii);
  return map;
}

Parser::Parser(uint32 sizeHint):
  Fsm(new NFA(1, sizeHint)),
  EncCodes(getEncodingsMap()),  // names -> uint
  Encoders(createEncodingMap()) // uint  -> Encoding object
{
  Fsm->TransFac = Nfab.getTransFac();
}

bool contains_possible_nongreedy(const std::string& pattern) {
  // The trailing '?' of a nongreedy operator must have at least
  // two characters preceeding it.
  return pattern.find('?', 2) != std::string::npos;
}

bool contains_possible_counted_repetition(const std::string& pattern) {
  // The '{' of a counted repetition operator must have at least one
  // character preceeding it and two characters following it.
  const std::string::size_type cr = pattern.rfind('{', pattern.length()-3);
  return cr > 0 && cr != std::string::npos;
}

void Parser::addPattern(const Pattern& pattern, uint32 patIndex)
{
//  std::cerr << "[" << patIndex << "]: " << pattern << std::endl; 
  // prepare the NFA builder
  Nfab.reset();
  Nfab.setCurLabel(patIndex);
  Nfab.setCaseInsensitive(pattern.CaseInsensitive);

  bool good = false;
  EncodingsCodeMap::const_iterator foundName(EncCodes.find(pattern.Encoding));
  if (foundName != EncCodes.end()) {
    EncodingMap::const_iterator    foundEncoder(Encoders.find(foundName->second));
    if (foundEncoder != Encoders.end()) {
      Nfab.setEncoding(foundEncoder->second);
      good = true;
    }
  }
  if (!good) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Unrecognized encoding '" << pattern.Encoding << "'"
    );
  }

  // parse the pattern
  if (parse(pattern.Expression, pattern.FixedString, Tree)) {
    // rewrite the parse tree, if necessary
    bool rewrite = false;

    if (contains_possible_nongreedy(pattern.Expression)) {
      rewrite |= reduce_trailing_nongreedy_then_empty(Tree.Root);
    }

    if (rewrite || contains_possible_counted_repetition(pattern.Expression)) {
      reduce_empty_subtrees(Tree.Root);
      reduce_useless_repetitions(Tree.Root);
    }

    // build the NFA for this pattern
    if (Nfab.build(Tree)) {
      // and merge it into the greater NFA
      Comp.pruneBranches(*Nfab.getFsm());
      Comp.mergeIntoFSM(*Fsm, *Nfab.getFsm());
      return;
    }
  }
  THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not parse " << pattern.Expression);
}
