#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <fstream>
#include "../includes/options.hpp"
#include "../includes/password.hpp"
#include "../includes/AES256.hpp"

inline bool exists_file(const std::string &filename)
{
    bool exists;
    std::ifstream encripted_file(filename);

    exists = encripted_file.good();
    encripted_file.close();

    return exists;
}

static inline void encrypt(const std::string filename)
{
    try {
        if (!exists_file("passwords.txt.enc")) {
            bool generated = generate_private_Key();

            if (!generated) return;
        }

        AES256_encrypt_file(filename);
        std::remove(filename.c_str());

    }
    catch (const std::exception& err) {
        std::cerr << "Error: " << err.what() << "\n";
    }
}

std::string generate_password(const std::string &arg)
{
    std::string password;

    try {
        int len = std::stoi(arg);
        password = generate_random_passwd(len);
    }
    catch (const std::invalid_argument& e) {
        std::string input = arg;
        password = generate_scrambled_passwd(input);
    }

    return password;
}

void add_credential(const std::string &platform, const std::string &username, const std::string &password)
{
    try {
        std::ofstream passwdDB(tempFile, std::ios::app);

        if (!passwdDB.is_open()) {
            std::cerr << "Failed to open file.\n";
            return;
        }

        if (exists_file("passwords.txt.enc")) {
            AES256_decrypt_file("passwords.txt.enc");
        }

        passwdDB << platform << ":" << username << ":" << password << "\n";

        passwdDB.close();

        encrypt(tempFile);
    }
    catch (const std::exception& err) {
        std::cerr << err.what();
    }
}

void show_credentials()
{
    try {
        AES256_decrypt_file("passwords.txt.enc");

        std::ifstream passwdDB(tempFile);
        std::string credential;

        while (std::getline(passwdDB, credential)) {
            std::cout << credential << "\n";
        }

        passwdDB.close();
        std::remove(tempFile.c_str());
    } 
    catch (const std::exception& err) {
        std::cerr << err.what();
    }
}
