/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2013, Lightbox Technologies, Inc

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
