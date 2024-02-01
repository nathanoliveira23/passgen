#pragma once

#include <string>
#include <openssl/evp.h>

bool generate_private_Key(const std::string&);
void AES256_encrypt_file(const std::string&);
void AES256_decrypt_file(const std::string&, const std::string&);
