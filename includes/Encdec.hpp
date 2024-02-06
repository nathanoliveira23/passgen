#pragma once

#include <array>
#include <string>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include "filepath.hpp"
#include "../includes/types.hpp"

namespace Encdec {
    namespace SHA256 {
        std::array<byte, SHA256_DIGEST_LENGTH> generate_sha256(const std::string&);
        bool sha256_match(const std::string&, std::array<byte, SHA256_DIGEST_LENGTH>);
    }

    namespace AES256 {
        bool generate_private_Key(const std::string&);
        void AES256_encrypt_file(const std::string&);
        void AES256_decrypt_file(const std::string&, const std::string&);
    }
}
