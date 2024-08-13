#pragma once

#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <unordered_map>

using std::array;
using std::vector;
using std::string;
using std::unordered_map;

class Password {
public:
    Password() = default;
    ~Password() = default;

    string generate_random_passwd(std::uint32_t);
    string generate_scrambled_passwd(std::string&);

private:
    string generate_random_str();

    static const vector<char> m_chars;
    static const unordered_map<char, vector<char>> m_correspondence;
};
