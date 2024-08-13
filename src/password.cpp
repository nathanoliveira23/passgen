#include <cstddef>

#include "../includes/password.hpp"
#include "../includes/random.hpp"

const vector<char> Password::m_chars = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
    'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
    'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 
    'y', 'z', '@', '#', '$', '%', '&',
};

const unordered_map<char, vector<char>> Password::m_correspondence = {
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

string Password::generate_random_str()
{
    string random_str;
    size_t rand = randInt(0, 5);

    for (std::size_t i = 0; i < rand; ++i) {
        std::size_t random_pos = randInt(0, m_chars.size() - 1);
        random_str.push_back(m_chars[random_pos]);
    }

    return random_str;
}

string Password::generate_random_passwd(std::uint32_t len)
{
    string password;

    for (size_t i = 0; i < len; i++) {
        size_t rand = randInt(0, m_chars.size() - 1);
        password.push_back(m_chars[rand]);
    }

    return password;    
}

string Password::generate_scrambled_passwd(std::string& str)
{
    string newPassword;
    string prefix, suffix;

    prefix = generate_random_str();
    suffix = generate_random_str();

    for (size_t i = 0; i < str.size(); ++i) {
        char char_to_change = str[i];

        if (m_correspondence.find(char_to_change) != m_correspondence.end()) {
            size_t pos = randInt(0, m_correspondence.at(char_to_change).size() - 1);
            str[i] = m_correspondence.at(char_to_change).at(pos);
        }
    }

    newPassword.append(prefix)
               .append(str)
               .append(suffix);

    return newPassword;
}
