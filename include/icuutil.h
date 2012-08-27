#pragma once

#include "basic.h"
#include "rangeset.h"

class USet;

void convUnicodeSet(UnicodeSet& dst, const USet* src);

void convUnicodeSet(USet* dst, const UnicodeSet& src);
