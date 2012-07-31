#pragma once

#include "basic.h"

#include <unicode/uset.h>

void convUnicodeSet(UnicodeSet& dst, const USet* src);

void convUnicodeSet(USet* dst, const UnicodeSet& src);
