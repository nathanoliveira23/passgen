#include <cstdint>
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <string>
#include <cstring>
#include <stdexcept>
#include <ios>
#include <fstream>

#include "../includes/password.hpp"
#include "../includes/SHA256.hpp"
#include "../includes/AES256.hpp"
#include "../includes/utils.hpp"

int main(int argc, char* argv[])
{
    if (argc > 1) {
        if (!strcmp(argv[1], "-g") || !strcmp(argv[1], "--generate")) {
            std::string passwordToGenerate;

            try {
                int len = std::stoi(argv[2]);
                passwordToGenerate = generate_random_passwd(len);
            }
            catch (const std::invalid_argument& e) {
                std::string input = argv[2];
                passwordToGenerate = generate_scrambled_passwd(input);
            }
            
            std::cout << passwordToGenerate << "\n";
        }
        else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "--add")) {
            std::string platform, username, password;

            try {
                std::ofstream passwdDB("passwords.txt", std::ios::app);

                platform = argv[2];
                username = argv[3];
                password = argv[4];

                passwdDB << platform << ":" << username << ":" << password << "\n";

                passwdDB.close();

                std::string private_key;

                char opt;
                std::cout << "Deseja gerar uma chave privada? [y/n] ";
                std::cin >> opt;

                if (std::tolower(opt) == 'y') {
                    private_key = generate_private_Key();
                    std::cout << private_key << "\n";
                    std::cout << "Esta e sua chave privada para criptografar e descriptografar este arquivo. Guarde-a em um local seguro.\n";
                }
                else if (std::tolower(opt) == 'n') {
                    std::cout << "Informe sua chave privada para criptografar o arquivo: ";
                    std::cin >> private_key;
                }
                else {
                    std::cout << "Informe uma opcao valida!\n";
                    std::abort();
                }

                std::string IV = AES256_encrypt_file("passwords.txt", private_key);
                std::remove("passwords.txt");

                std::ofstream IVfile("iv.txt");
                IVfile << IV.data();
                IVfile.close();
            }
            catch (const std::exception& err) {
                std::cerr << err.what() << "\n";
            }
        }
        else if (!strcmp(argv[1], "-l") || !strcmp(argv[1], "--list")) {
            try {
                std::string iv;

                std::ifstream ivfile("iv.txt");
                std::getline(ivfile, iv);
                ivfile.close();

                std::string pk;
                std::cout << "Informe a chave privada: ";
                std::cin >> pk;

                AES256_decrypt_file("passwords.dat", pk, iv);

                std::ifstream passwdDB("passwords.txt");
                std::string buffer;

                while (getline(passwdDB, buffer)) {
                    std::cout << buffer << "\n";
                }

                passwdDB.close();
                std::remove("passwords.txt");
            }
            catch (const std::exception& err) {
                std::cerr << err.what() << "\n";
            }
        }
        else {
            return 1;
        }
    }

    return 0;
}
