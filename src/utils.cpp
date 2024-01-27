#include <sstream>
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
