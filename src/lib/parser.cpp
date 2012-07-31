#include "concrete_encoders.h"
#include "encoder.h"
#include "encodings.h"
#include "parser.h"
#include "rewriter.h"

#include <string>
#include <memory>

Parser::Parser(uint32 sizeHint):
  Fsm(new NFA(1, sizeHint)),
  Encoders{
    { "ASCII",    std::make_shared<ASCII>()          },
    { "UTF-8",    std::make_shared<CachingUTF8>()    },
    { "UTF-16LE", std::make_shared<CachingUTF16LE>() },
    { "UTF-16BE", std::make_shared<CachingUTF16BE>() },
    { "UTF-32LE", std::make_shared<CachingUTF32LE>() },
    { "UTF-32BE", std::make_shared<CachingUTF32BE>() }
  }
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

void Parser::addPattern(const Pattern& pattern, uint32 patIndex) {
  // prepare the NFA builder
  Nfab.reset();
  Nfab.setCurLabel(patIndex);

  // set the character encoding
  auto i = Encoders.find(pattern.Encoding);
  if (i != Encoders.end()) {
    Nfab.setEncoder(i->second);
  }
  else {
    std::shared_ptr<Encoder> enc(
      new CachingICUEncoder(pattern.Encoding.c_str())
    );
    Encoders.insert(std::make_pair(pattern.Encoding, enc));
    Nfab.setEncoder(enc);
  }

  // parse the pattern
  if (parse(pattern, Tree)) {
    // rewrite the parse tree, if necessary
    bool rewrite = false;

    rewrite = make_binops_right_associative(Tree.Root);
    rewrite |= combine_consecutive_repetitions(Tree.Root);

    if (contains_possible_nongreedy(pattern.Expression)) {
      rewrite |= reduce_trailing_nongreedy_then_empty(Tree.Root);
      rewrite |= reduce_trailing_nongreedy_then_greedy(Tree.Root);
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
    else {
      THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("Empty matches");
    }
  }

  THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("Could not parse");
}
