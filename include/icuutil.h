#pragma once

#include "basic.h"

#include <unicode/uniset.h>

void convUnicodeSet(::UnicodeSet& dst, const icu::UnicodeSet& src);

void convUnicodeSet(icu::UnicodeSet& dst, const ::UnicodeSet& src);
