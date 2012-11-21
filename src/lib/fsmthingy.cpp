#include "concrete_encoders.h"
#include "encoder.h"
#include "fsmthingy.h"
#include "identitybyteencoder.h"
#include "identitycharencoder.h"
#include "lightgrep_c_util.h"
#include "lightgrep_c_char_char_trans.h"
#include "lightgrep_c_char_byte_trans.h"
#include "lightgrep_c_byte_byte_trans.h"
#include "oceencoder.h"
#include "rotencoder.h"
#include "xorencoder.h"

#include <memory>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

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
  Nfab.setEncoder(buildEncoder(chain));

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

std::shared_ptr<Encoder> FSMThingy::buildEncoder(const std::string& chain) {
  typedef boost::char_separator<char> char_separator;
  typedef boost::tokenizer<char_separator> tokenizer;

  const tokenizer tokens(chain, char_separator("|"));
  tokenizer::const_iterator curTok(tokens.begin());
  const tokenizer::const_iterator endTok(tokens.end());

  int id;

  // process the char->char transformations
  std::vector<std::string> charchar;
  for ( ; curTok != endTok; ++curTok) {
    id = lg_get_char_char_transformation_id(curTok->c_str());
    if (id < 0) {
      break;
    }

    charchar.emplace_back(LG_CANONICAL_CHAR_CHAR_TRANSFORMATIONS[id]);
  }

  if (curTok == endTok) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT("No valid char->byte transformation");
  }

  // process the char->byte transformation
  id = lg_get_char_byte_transformation_id(curTok->c_str());
  if (id < 0) {
    THROW_RUNTIME_ERROR_WITH_OUTPUT(
      "'" << *curTok << "' is neither a valid char->char transformation "
      "nor a valid char->byte transformation"
    );
  }

  const std::string charbyte = LG_CANONICAL_CHAR_BYTE_TRANSFORMATIONS[id];
  ++curTok;

  // process the byte->byte transformations
  std::vector<std::string> bytebyte;
  for ( ; curTok != endTok; ++curTok) {
    id = lg_get_byte_byte_transformation_id(curTok->c_str());
    if (id < 0) {
      THROW_RUNTIME_ERROR_WITH_OUTPUT(
        "'" << *curTok << "' is not a valid byte->byte transformation"
      );
    }

    bytebyte.emplace_back(LG_CANONICAL_BYTE_BYTE_TRANSFORMATIONS[id]);
  }

  // assemble the transformation chain 
  
  std::unique_ptr<Encoder> enc;

  if (charbyte == "ASCII") {
    enc.reset(new ASCII);
  }
  else if (charbyte == "UTF-8") {
    enc.reset(new UTF8);
  }
  else if (charbyte == "UTF-16LE") {
    enc.reset(new UTF16LE);
  }
  else if (charbyte == "UTF-16BE") {
    enc.reset(new UTF16BE);
  }
  else if (charbyte == "UTF-32LE") {
    enc.reset(new UTF32LE);
  }
  else if (charbyte == "UTF-32BE") {
    enc.reset(new UTF32BE);
  }
  else {
    enc.reset(new ICUEncoder(charbyte));
  }

  for (const std::string& bb : bytebyte) {
    if (bb == "identity") {
      enc.reset(new IdentityByteEncoder(std::move(enc)));
    }
    else if (bb == "OCE") {
      enc.reset(new OCEEncoder(std::move(enc)));
    }
  }

  for (auto cc = charchar.crbegin(); cc != charchar.crend(); ++cc) {
    if (*cc == "identity") {
      enc.reset(new IdentityCharEncoder(std::move(enc)));
    }
    else if (cc->substr(0, 3) == "rot") {
      enc.reset(new ROTEncoder(
        boost::lexical_cast<uint32>(cc->substr(3)), std::move(enc)
      ));
    }
    else if (cc->substr(0, 3) == "XOR") {
      enc.reset(new XOREncoder(
        boost::lexical_cast<byte>(cc->substr(3)), std::move(enc)
      ));
    }
  }

  return std::shared_ptr<Encoder>(enc.release());
}
