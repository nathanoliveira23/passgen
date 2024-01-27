#include <cstddef>
#include <fstream> 
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <array>
#include <iomanip>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include "../includes/AES256.hpp"

inline static void encrypt_error(std::string error = "failed to encrypt file\n")
{
    std::cerr << "Error: " << error;
    std::abort();
}

inline static void decrypt_error(std::string error = "failed to decrypt file\n")
{
    std::cerr << "Error: " << error;
    std::abort();
}

static std::array<std::uint8_t, EVP_MAX_IV_LENGTH> generate_IV()
{
    std::array<std::uint8_t, EVP_MAX_IV_LENGTH> IV;

    int success = RAND_bytes(IV.data(), EVP_MAX_IV_LENGTH);

    if (success != 1) {
        encrypt_error();
    }

    return IV;
}

std::string binToHex()
{
    std::array<uint8_t, EVP_MAX_IV_LENGTH> IV = generate_IV();
    std::stringstream ASCIV;

    for (std::size_t i = 0; i < EVP_MAX_IV_LENGTH; ++i) {
        ASCIV << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(IV[i]);
    }

    return ASCIV.str();
}

std::string generate_private_Key()
{
    std::uint8_t binKey[EVP_MAX_KEY_LENGTH];
    int success = RAND_bytes(binKey, EVP_MAX_KEY_LENGTH);

    if (success != 1) {
        encrypt_error("failed to generate private Key\n");
    }

    std::stringstream ASCKey;
    for (std::size_t i = 0; i < EVP_MAX_KEY_LENGTH; ++i)
        ASCKey << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(binKey[i]);

    return ASCKey.str();
}

std::string AES256_encrypt_file(const std::string &input_file, const std::string& private_key)
{
    OpenSSL_add_all_algorithms();

    //std::array<std::uint8_t, EVP_MAX_IV_LENGTH> IV = generate_IV();
    std::string IV = binToHex();

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        encrypt_error();
    }

    int encrypt_init = EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const uint8_t*>(private_key.c_str()), reinterpret_cast<const uint8_t*>(IV.c_str()));

    if (encrypt_init != 1) {
        encrypt_error();
    }

    std::ifstream to_encrypt_file(input_file, std::ios::binary);
    std::ofstream encrypted_file("passwords.dat", std::ios::binary);

    std::uint8_t inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, bytes_written;

    while ((bytes_read = to_encrypt_file.read(reinterpret_cast<char*>(inbuf), sizeof(inbuf)).gcount()) > 0) {
        if (EVP_EncryptUpdate(ctx, outbuf, &bytes_written, inbuf, bytes_read) != 1) {
            encrypt_error();
        }
        encrypted_file.write(reinterpret_cast<char*>(outbuf), bytes_written);
    }

    if (EVP_EncryptFinal_ex(ctx, outbuf, &bytes_written) != 1) {
        encrypt_error();
    }

    encrypted_file.write(reinterpret_cast<char*>(outbuf), bytes_written);

    EVP_CIPHER_CTX_free(ctx);
    to_encrypt_file.close();
    encrypted_file.close();

    return IV;
}

void AES256_decrypt_file(const std::string &encrypted_file, const std::string &private_key, const std::string &iv) 
{
    OpenSSL_add_all_algorithms();

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        decrypt_error();
    }

    int success = EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, reinterpret_cast<const uint8_t*>(private_key.c_str()), reinterpret_cast<const uint8_t*>(iv.c_str()));

    if (success != 1) {
        decrypt_error();
    }

    std::ifstream infile(encrypted_file, std::ios::binary);
    std::ofstream outfile("passwords.txt", std::ios::binary);

    uint8_t inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, bytes_written;

    while ((bytes_read = infile.read(reinterpret_cast<char*>(inbuf), sizeof(inbuf)).gcount()) > 0) {
        if (EVP_DecryptUpdate(ctx, outbuf, &bytes_written, inbuf, bytes_read) != 1) {
            decrypt_error();
        }

        outfile.write(reinterpret_cast<char*>(outbuf), bytes_written);
    }
    
    if (EVP_DecryptFinal(ctx, outbuf, &bytes_written) != 1) {
        decrypt_error();
    }
    
    outfile.write(reinterpret_cast<char*>(outbuf), bytes_written);

    EVP_CIPHER_CTX_free(ctx);
    infile.close();
    outfile.close();
}
