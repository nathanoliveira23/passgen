#include "../includes/password.hpp"
#include "../includes/random.hpp"
#include <cstddef>

static std::string generate_random_str()
{
    std::string random_str;
    std::size_t rand = randInt(0, 5);

    for (std::size_t i = 0; i < rand; ++i) {
        std::size_t random_pos = randInt(0, SIZE - 1);
        random_str.push_back(chars[random_pos]);
    }

    return random_str;
}

std::string generate_random_passwd(std::uint32_t len)
{
    std::string password;

    for (std::size_t i = 0; i < len; i++) {
        std::size_t rand = randInt(0, SIZE - 1);
        password.push_back(chars[rand]);
    }

    return password;    
}

std::string generate_scrambled_passwd(std::string& str)
{
    std::string newPassword;
    std::string prefix, suffix;

    prefix = generate_random_str();
    suffix = generate_random_str();

    for (std::size_t i = 0; i < str.size(); ++i) {
        char toChange = str[i];

        if (correspondence.count(toChange)) {
            std::size_t pos = randInt(0, correspondence[toChange].size() - 1);
            str[i] = correspondence[toChange].at(pos);
        }
    }


    newPassword.append(prefix)
               .append(str)
               .append(suffix);

    return newPassword;
}
