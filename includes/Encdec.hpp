#pragma once

#include <array>
#include <string>
#include <openssl/evp.h>
#include <openssl/sha.h>

#include "filepath.hpp"
#include "../includes/types.hpp"

using std::array;
using std::string;

namespace EncDec {

class SHA256 {
public:
    SHA256() = default;
    ~SHA256() = default;

    static array<byte, SHA256_DIGEST_LENGTH> generate_sha256(const string&); 
    static bool sha256_match(const string&, const array<byte, SHA256_DIGEST_LENGTH>&);
};

class AES256 {
public:
    AES256() = default;
    AES256(const string &file) : m_filepath(file) { /* empty */ }
    ~AES256() = default;

    static bool generate_private_Key(const string&);
    void encrypt_file();
    void decrypt_file(const string&);

private:
    string m_filepath;
};

} // NAMESPACE ENCDEC
