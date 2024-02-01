#define OPENSSL_API_COMPAT 3000
#define OPENSSL_NO_DEPRECATED 1

#include <cstddef>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>
#include "../includes/SHA256.hpp"

std::array<byte, SHA256_DIGEST_LENGTH> generate_sha256(const std::string& passwd)
{
    std::array<byte, SHA256_DIGEST_LENGTH> hash;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, passwd.c_str(), passwd.length());
    SHA256_Final(hash.data(), &sha256);

    return hash;
}

bool sha256_match(const std::string& passwd, std::array<byte, SHA256_DIGEST_LENGTH> hashpasswd)
{
    std::array<byte, SHA256_DIGEST_LENGTH> hash = generate_sha256(passwd);

    for (std::size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        if (hashpasswd[i] != hash[i])
            return false;
    }

    return true;
}
