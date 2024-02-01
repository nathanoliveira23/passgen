#pragma once

#include <vector>
#include <string>
#include <cstddef>
#include "types.h"

namespace Ultil {
    std::vector<std::string> split(const std::string&, char);
    std::string tobase64(byte [], std::size_t);
}
