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

inline static void encdec_error(const std::string& error)
{
    std::cerr << "Error: " << error;
    std::abort();
}

bool generate_private_Key()
{
    byte key[EVP_MAX_KEY_LENGTH];
    int success = RAND_bytes(key, EVP_MAX_KEY_LENGTH);

    if (success != 1) {
        encdec_error("Failed to generate private Key.\n");
        return false;
    }

    std::ofstream secKeyFile("secret.key", std::ios::binary);

    if (!secKeyFile.is_open()) {
        std::cerr << "Failed to create private key file.\n";
        return false;
    }

    secKeyFile.write(reinterpret_cast<char*>(key), EVP_MAX_KEY_LENGTH);
    secKeyFile.close();
    
    return true;
}

void AES256_encrypt_file(const std::string &input_file)
{
    OpenSSL_add_all_algorithms();

    byte iv[EVP_MAX_IV_LENGTH];
    byte pkey[EVP_MAX_KEY_LENGTH];

    std::ifstream pkfile("secret.key", std::ios::binary);

    pkfile.read(reinterpret_cast<char*>(pkey), EVP_MAX_KEY_LENGTH);

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        encdec_error("Failed to initialize context.\n");
        EVP_CIPHER_CTX_free(ctx);
    }

    int encrypt_init = EVP_EncryptInit_ex(ctx, 
                                        EVP_aes_256_cbc(), 
                                        nullptr, 
                                        pkey, 
                                        iv);

    if (encrypt_init != 1) {
        encdec_error("Failed to encrypt initialize.\n");
        EVP_CIPHER_CTX_free(ctx);
    }

    std::ifstream to_encrypt_file(input_file, std::ios::binary);
    std::ofstream encrypted_file("passwords.txt.enc", std::ios::binary);

    encrypted_file.write(reinterpret_cast<char*>(iv), EVP_MAX_IV_LENGTH);

    byte inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, bytes_written;

    while ((bytes_read = to_encrypt_file.read(reinterpret_cast<char*>(inbuf), sizeof(inbuf)).gcount()) > 0) {
        if (EVP_EncryptUpdate(ctx, outbuf, &bytes_written, inbuf, bytes_read) != 1) {
            encdec_error("Failed to encrypt file.\n");
            EVP_CIPHER_CTX_free(ctx);
        }
        encrypted_file.write(reinterpret_cast<char*>(outbuf), bytes_written);
    }

    if (EVP_EncryptFinal_ex(ctx, outbuf, &bytes_written) != 1) {
        encdec_error("Failed to encrypt file.\n");
        EVP_CIPHER_CTX_free(ctx);
    }

    encrypted_file.write(reinterpret_cast<char*>(outbuf), bytes_written);

    EVP_CIPHER_CTX_free(ctx);

    to_encrypt_file.close();
    encrypted_file.close();
    pkfile.close();
}

void AES256_decrypt_file(const std::string &encrypted_file) 
{
    OpenSSL_add_all_algorithms();

    std::ifstream infile(encrypted_file, std::ios::binary);
    std::ifstream pkfile("secret.key", std::ios::binary);

    byte iv[EVP_MAX_IV_LENGTH];
    byte pkey[EVP_MAX_KEY_LENGTH];

    infile.read(reinterpret_cast<char*>(iv), EVP_MAX_IV_LENGTH);
    pkfile.read(reinterpret_cast<char*>(pkey), EVP_MAX_KEY_LENGTH);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    if (!ctx) {
        encdec_error("Failed to initialize context.\n");
        EVP_CIPHER_CTX_free(ctx);
    }

    int success = EVP_DecryptInit_ex(ctx, 
                                    EVP_aes_256_cbc(), 
                                    nullptr, 
                                    pkey, 
                                    iv);

    if (success != 1) {
        encdec_error("Failed to decrypt initialize.\n");
        EVP_CIPHER_CTX_free(ctx);
    }

    std::ofstream outfile("passwords.txt", std::ios::binary);

    byte inbuf[1024], outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
    int bytes_read, bytes_written;

    while ((bytes_read = infile.read(reinterpret_cast<char*>(inbuf), sizeof(inbuf)).gcount()) > 0) {
        if (EVP_DecryptUpdate(ctx, outbuf, &bytes_written, inbuf, bytes_read) != 1) {
            encdec_error("Failed to decrypt file.\n");
            EVP_CIPHER_CTX_free(ctx);
        }

        outfile.write(reinterpret_cast<char*>(outbuf), bytes_written);
    }
    
    if (EVP_DecryptFinal(ctx, outbuf, &bytes_written) != 1) {
        encdec_error("Failed to decrypt file.\n");
        EVP_CIPHER_CTX_free(ctx);
    }
    
    outfile.write(reinterpret_cast<char*>(outbuf), bytes_written);

    EVP_CIPHER_CTX_free(ctx);

    infile.close();
    pkfile.close();
    outfile.close();
}
