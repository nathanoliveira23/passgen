#include <iomanip>
#include <sstream>
#include <cstdio>
#include <array>
#include <string>
#include "../includes/utils.hpp"

std::vector<std::string> Ultil::split(const std::string& str, char delimiter)
{
    std::vector<std::string> splitstr;

    std::stringstream check1(str);
    std::string splits;

    while (std::getline(check1, splits, delimiter))
        splitstr.push_back(splits);

    return splitstr;
}

std::string Ultil::tobase64(byte bincode[], std::size_t len)
{
    std::stringstream base64;
    
    for (std::size_t i = 0; i < len; ++i) {
        base64 << std::hex
               << std::setw(2)
               << std::setfill('0')
               << static_cast<int>(bincode[i]);
    }

    return base64.str();
}

