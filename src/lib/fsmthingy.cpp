#include "concrete_encoders.h"
#include "encoder.h"
#include "encodings.h"
#include "fsmthingy.h"
#include "oceencoder.h"

#include <string>
#include <memory>

FSMThingy::FSMThingy(uint32 sizeHint):
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

void FSMThingy::addPattern(const ParseTree& tree, const char* ename, uint32 label) {
  // prepare the NFA builder
  Nfab.reset();
  Nfab.setCurLabel(label);

  // set the character encoding

  std::unique_ptr<Encoder> enc; 

  auto i = Encoders.find(ename);
  if (i != Encoders.end()) {
    enc.reset(i->second->clone());
  }
  else {
    enc.reset(new ICUEncoder(ename));
  }

/*
  ++e;
  for (auto end = pattern.Encoding.crend(); e != end; ++e) {
    if (*e == "OCE") {
// FIXME: leak?
      enc.reset(new OCEEncoder(std::move(enc)));
    }
  }
*/

  Nfab.setEncoder(std::shared_ptr<Encoder>(std::move(enc)));

  // build the NFA for this pattern
  if (Nfab.build(tree)) {
    // and merge it into the greater NFA
    Comp.pruneBranches(*Nfab.getFsm());
    Comp.mergeIntoFSM(*Fsm, *Nfab.getFsm());
  }
  else {
    THROW_RUNTIME_ERROR_WITH_CLEAN_OUTPUT("Empty matches");
  }
}

void FSMThingy::finalizeGraph(bool determinize) {
  if (Fsm->verticesSize() < 2) {
    throw std::runtime_error("No valid patterns were parsed");
  }

  if (determinize && !Fsm->Deterministic) {
    NFAPtr dfa(new NFA(1, 2 * Fsm->verticesSize(), Fsm->edgesSize()));
    dfa->TransFac = Fsm->TransFac;
    Comp.subsetDFA(*dfa, *Fsm);
    Fsm = dfa;
  }

  Comp.labelGuardStates(*Fsm);
}
