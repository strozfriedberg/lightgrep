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
    THROW_RUNTIME_ERROR_WITH_OUTPUT("Unrecognized encoding '" << encoding << "'");
  }

  // parse the pattern
  if (parse(pattern, keyOpts.FixedString, Tree)) {
    // rewrite the parse tree, if necessary
    bool rewritten = false;
    if (pattern.find('?',1) != std::string::npos) {
      rewritten |= reduce_trailing_nongreedy_then_empty(Tree.Root);
    }

    if (rewritten || pattern.find('{',1) != std::string::npos) {
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
