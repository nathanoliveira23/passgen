#pragma once

#include <string>
#include <openssl/evp.h>

typedef unsigned char byte;

bool generate_private_Key();
void AES256_encrypt_file(const std::string& input_file);
void AES256_decrypt_file(const std::string& encrypted_file);
