#pragma once

#include <ostream>
#include <string>

std::string formatTimestamp(int64_t unix_time, uint32_t ns, std::ostringstream& buf);
