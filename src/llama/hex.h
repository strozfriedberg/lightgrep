#pragma once

#include <string>

std::string hexEncode(const void* buf, size_t size);

std::string hexEncode(const void* beg, const void* end);
