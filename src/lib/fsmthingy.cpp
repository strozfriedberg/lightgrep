/*
 * Copyright 2024 Aon Cyber Solutions
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "fsmthingy.h"
#include "encoders/encoder.h"

#include <memory>
#include <string>
#include <vector>

FSMThingy::FSMThingy(uint32_t sizeHint): Fsm(new NFA(1, sizeHint)) {
  Fsm->TransFac = Nfab.getTransFac();
}

void FSMThingy::addPattern(const ParseTree& tree, const char* chain, uint32_t label) {
  // prepare the NFA builder
  Nfab.reset();
  Nfab.setCurLabel(label);

  // set the character encoding
  Nfab.setEncoder(EncFac.get(chain));

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

void FSMThingy::finalizeGraph(uint32_t determinizeDepth) {
  if (Fsm->verticesSize() < 2) {
    throw std::runtime_error("No valid patterns were parsed");
  }

  if (determinizeDepth && !Fsm->Deterministic) {
    NFAPtr dfa(new NFA(1, 2 * Fsm->verticesSize(), Fsm->edgesSize()));
    dfa->TransFac = Fsm->TransFac;
    Comp.subsetDFA(*dfa, *Fsm, determinizeDepth);
    Fsm = dfa;
  }

  Comp.labelGuardStates(*Fsm);
}
