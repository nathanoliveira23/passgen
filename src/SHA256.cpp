#define OPENSSL_API_COMPAT 3000
#define OPENSSL_NO_DEPRECATED 1

#include <cstddef>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include "../includes/SHA256.hpp"

std::string generate_sha256(const std::string& passwd)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, passwd.c_str(), passwd.length());
    SHA256_Final(hash, &sha256);

    std::stringstream hashpasswd;

    for (std::size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        hashpasswd << std::hex
                   << std::setw(2)
                   << std::setfill('0')
                   << static_cast<int>(hash[i]);

    return hashpasswd.str();
}

bool sha256_match(const std::string& passwd, const std::string& hashpasswd)
{
    const std::string hash = generate_sha256(passwd);

    bool hash_match = hash == hashpasswd;

    return hash_match;
}
