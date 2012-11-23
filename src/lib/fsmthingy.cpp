/*
  liblightgrep: not the worst forensics regexp engine
  Copyright (C) 2012 Lightbox Technologies, Inc

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

#include "concrete_encoders.h"
#include "encoder.h"
#include "fsmthingy.h"

#include <memory>
#include <string>
#include <vector>

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

void FSMThingy::addPattern(const ParseTree& tree, const char* chain, uint32 label) {
  // prepare the NFA builder
  Nfab.reset();
  Nfab.setCurLabel(label);

  // set the character encoding
  Nfab.setEncoder(EncFac.get(chain));

/*
  std::unique_ptr<Encoder> enc; 

  auto i = Encoders.find(ename);
  if (i != Encoders.end()) {
    enc.reset(i->second->clone());
  }
  else {
    enc.reset(new ICUEncoder(ename));
  }
*/

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
