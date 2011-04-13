#pragma once

#include "basic.h"
#include "parsetree.h"

#include <string>

std::string byteToCharacterString(uint32 i); 
std::string byteSetToCharacterClass(const ByteSet& bs);

std::string unparse(const ParseTree& tree); 

