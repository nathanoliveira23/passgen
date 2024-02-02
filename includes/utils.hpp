#pragma once

#include <array>
#include <vector>
#include <string>
#include <cstddef>
#include "types.hpp"

namespace Ultil {
    std::vector<std::string> split(const std::string&, char);
    std::string tobase64(byte [], std::size_t);
}
