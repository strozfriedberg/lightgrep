#pragma once

#include <bitset>
#include <exception>
#include <sstream>
#include <vector>
#include <utility>
#include <boost/smart_ptr.hpp>

typedef unsigned char byte;

typedef unsigned int uint32;
typedef int int32;

typedef unsigned long long uint64;
typedef long long int64;

typedef std::bitset<256> ByteSet;

#define THROW_WITH_OUTPUT(exceptType, expression) \
  std::stringstream buf; \
  buf << __FILE__ << ":" << __LINE__ << ": " << expression; \
  throw exceptType(buf.str())

#define THROW_RUNTIME_ERROR_WITH_OUTPUT(expression) THROW_WITH_OUTPUT(std::runtime_error, expression)
