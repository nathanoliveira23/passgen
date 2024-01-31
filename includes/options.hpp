#pragma once

#include <string>

static const std::string tempFile = "passwords.txt";

std::string generate_password(const std::string &arg);
void add_credential(const std::string &platform, const std::string &username, const std::string &password);
void show_credentials();
