#include <array>
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <fstream>
#include "../includes/options.hpp"
#include "../includes/password.hpp"
#include "../includes/AES256.hpp"
#include "../includes/utils.hpp"
#include "../includes/filepath.hpp"
#include "../includes/table.hpp"

static inline bool exists_file(const std::string &filename)
{
    bool exists;
    std::ifstream encripted_file(filename);

    exists = encripted_file.good();
    encripted_file.close();

    return exists;
}

static inline void encrypt(const std::string filename, const std::string passphrase)
{
    try {
        if (!exists_file(ENCFILE)) {
            bool generated = generate_private_Key(passphrase);

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
    std::string userPassphrase;

    try {
        std::ofstream passwdDB(TEMPFILE, std::ios::app);

        if (!passwdDB.is_open()) {
            std::cerr << "Failed to open file.\n";
            return;
        }

        if (exists_file(ENCFILE)) {
            std::cout << "Your passphrase: ";
            std::cin >> userPassphrase;

            AES256_decrypt_file(ENCFILE, userPassphrase);
        }
        else {
            std::cout << "Enter a new passphrase: ";
            std::cin >> userPassphrase;
        }

        passwdDB << platform << ":" << username << ":" << password << "\n";

        passwdDB.close();

        encrypt(TEMPFILE, userPassphrase);
    }
    catch (const std::exception& err) {
        std::cerr << err.what();
    }
}

void show_credentials()
{
    std::string userPassphrase;

    std::cout << "Your passphrase: ";
    std::cin >> userPassphrase;

    try {
        AES256_decrypt_file(ENCFILE, userPassphrase);

        std::ifstream passwdDB(TEMPFILE);
        std::string credential;

        drawTableHeader();
        while (std::getline(passwdDB, credential)) {
            std::vector<std::string> userCredentials = Ultil::split(credential, ':');
            drawTable(userCredentials);
        }

        passwdDB.close();
        std::remove(TEMPFILE.c_str());
    } 
    catch (const std::exception& err) {
        std::cerr << err.what();
    }
}
