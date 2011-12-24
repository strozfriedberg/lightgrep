#include "parser.h"
#include "encodings.h"
#include "encoding.h"
#include "concrete_encodings.h"
#include "rewriter.h"


typedef std::map< std::string, boost::shared_ptr<Encoding> > EncodingMap;

EncodingMap createEncodingMap() {
  EncodingMap map;
  map[LG_SUPPORTED_ENCODINGS[LG_ENC_ASCII]].reset(new Ascii);
  map[LG_SUPPORTED_ENCODINGS[LG_ENC_UTF_16]].reset(new UCS16);
  return map;
}

const EncodingMap& getEncodings() {
  static EncodingMap map(createEncodingMap());
  return map;
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

void Parser::addPattern(const std::string& pattern, uint32 patIndex, const LG_KeyOptions& keyOpts)
{
  // prepare the NFA builder
  Nfab.reset();
  Nfab.setCurLabel(patIndex);
  Nfab.setCaseSensitive(!keyOpts.CaseInsensitive);

  std::string encoding(keyOpts.Encoding);
  EncodingMap::const_iterator foundEnc(getEncodings().find(encoding));
  if (foundEnc != getEncodings().end()) {
    Nfab.setEncoding(foundEnc->second);
  }
  else {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "Unrecognized encoding '" << encoding << "'"
    );
  }

  // parse the pattern
  if (parse(pattern, keyOpts.FixedString, Tree)) {
    // rewrite the parse tree, if necessary
    bool rewrite = false;

    if (contains_possible_nongreedy(pattern)) {
      rewrite |= reduce_trailing_nongreedy_then_empty(Tree.Root);
    }

    if (rewrite || contains_possible_counted_repetition(pattern)) {
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
  THROW_RUNTIME_ERROR_WITH_OUTPUT("Could not parse " << pattern);
}
