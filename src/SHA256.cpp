#define OPENSSL_API_COMPAT 3000
#define OPENSSL_NO_DEPRECATED 1

#include <cstddef>
#include <openssl/sha.h>

#include "../includes/Encdec.hpp"

namespace EncDec {

std::array<byte, SHA256_DIGEST_LENGTH> SHA256::generate_sha256(const std::string& passwd)
{
    std::array<byte, SHA256_DIGEST_LENGTH> hash;

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, passwd.c_str(), passwd.length());
    SHA256_Final(hash.data(), &sha256);

    return hash;
}

bool SHA256::sha256_match(const string& passwd, const array<byte, SHA256_DIGEST_LENGTH> &hashpasswd)
{
    std::array<byte, SHA256_DIGEST_LENGTH> hash = generate_sha256(passwd);

    for (std::size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        if (hashpasswd[i] != hash[i])
            return false;
    }

    return true;
}

} // NAMESPACE ENCDEC

