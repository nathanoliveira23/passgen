#include "../includes/password.hpp"
#include "../includes/random.hpp"

std::string generate(std::uint32_t len)
{
    std::string password;

    for (std::size_t i = 0; i < len; i++) {
        std::size_t rand = randInt(0, SIZE - 1);
        password.push_back(chars[rand]);
    }

    return password;    
}

std::string generate_v2(std::string& str)
{
    std::string newPassword;
    std::size_t rand = randInt(1, 5);

    for (std::size_t i = 0; i < rand; ++i) {
        std::size_t pos = randInt(0, SIZE - 1);
        newPassword.push_back(chars[pos]);
    }

    for (std::size_t i = 0; i < str.size(); ++i) {
        char toChange = str[i];

        if (correspondence.count(toChange))
            str[i] = correspondence[toChange];
    }

    newPassword += str;

    rand = randInt(1, 5);

    for (std::size_t i = 0; i < rand; ++i) {
        std::size_t pos = randInt(0, SIZE - 1);
        newPassword.push_back(chars[pos]);
    }

    return newPassword;
}
