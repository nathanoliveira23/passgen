#pragma once

#include <string>

static const std::string tempFile = "passwords.txt";

std::string generate_password(const std::string&);
void add_credential(const std::string&, const std::string&, const std::string&);
void show_credentials();
