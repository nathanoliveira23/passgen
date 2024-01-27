#pragma once

#include <cstdint>
#include <string>
#include <array>
#include <openssl/evp.h>

std::string generate_private_Key();
std::string AES256_encrypt_file(const std::string& input_file, const std::string& private_key);
void AES256_decrypt_file(const std::string& encrypted_file, const std::string& private_key, const std::string &iv);
