#pragma once

#include <string>
#include <vector>

typedef struct {
    std::string url, username, password;
} COLDATA;

std::string generate_password(const std::string&);
void add_credential(const std::string&, const std::string&, const std::string&);
void show_credentials();
