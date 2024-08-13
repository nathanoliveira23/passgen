#include <iostream>
#include <cstdlib>
#include <cctype>
#include <cstdio>
#include <string>
#include <cstring>

#include "../includes/options.hpp"

int main(int argc, char* argv[])
{
    if (argc > 1) {
        if (!strcmp(argv[1], "-g") || !strcmp(argv[1], "--generate")) {
            std::string passwordToGenerate = generate_password(argv[2]);
            
            std::cout << passwordToGenerate << "\n";
        }
        else if (!strcmp(argv[1], "-a") || !strcmp(argv[1], "--add")) {
            add_credential(argv[2], argv[3], argv[4]);
        }
        else if (!strcmp(argv[1], "-l") || !strcmp(argv[1], "--list")) {
            show_credentials();
        }
        else {
            return 1;
        }
    }

    return 0;
}
