#pragma once

#include <string>
#include <cstdint>
#include <array>
#include <vector>
#include <unordered_map>

#define SIZE 67

static const std::array<char, SIZE> chars = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 
    'y', 'z', '@', '#', '$', '%', '&'
};

static std::unordered_map<char, std::vector<char>> correspondence = {
    { 'a', { 'A', 'a', '@', '4' } },
    { 'b', { 'B', 'b', '6' } },
    { 'c', { 'C', 'c' } },
    { 'd', { 'D', 'd' } },
    { 'e', { 'E', 'e', '&', '3' } },
    { 'f', { 'F', 'f' } },
    { 'g', { 'G', 'g', '&', '9' } },
    { 'h', { 'H', 'h', '#' } },
    { 'i', { 'I', 'i', '1' } },
    { 'j', { 'J', 'j' } },
    { 'k', { 'K', 'k' } },
    { 'l', { 'L', 'l', '1' } },
    { 'm', { 'M', 'm' } },
    { 'n', { 'N', 'n' } },
    { 'o', { 'O', 'o', '0' } },
    { 'p', { 'P', 'p' } },
    { 'q', { 'Q', 'q', '9' } },
    { 'r', { 'R', 'r' } },
    { 's', { 'S', 's', '$', '5' } },
    { 't', { 'T', 't', '7' } },
    { 'u', { 'U', 'u' } },
    { 'v', { 'V', 'v' } },
    { 'w', { 'W', 'w' } },
    { 'x', { 'X', 'x' } },
    { 'y', { 'Y', 'y', '7' } },
    { 'z', { 'Z', 'z', '2' } }
};

std::string generate_random_passwd(std::uint32_t);
std::string generate_scrambled_passwd(std::string&);
