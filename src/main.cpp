#include <iostream>
#include <cstring>
#include <stdexcept>

#include "../includes/password.hpp"

int main(int argc, char* argv[])
{
    if (argc > 0) {
        if (!strcmp(argv[1], "-g") || !strcmp(argv[1], "--generate")) {
            std::string length, passwordToGenerate;

            try {
                int len = std::stoi(argv[2]);

                passwordToGenerate = generate(len);
            }
            catch (const std::invalid_argument& e) {
                std::string input = argv[2];
                passwordToGenerate = generate_v2(input);
            }
            
            std::cout << passwordToGenerate << "\n";
        }
    }

    return 0;
}
