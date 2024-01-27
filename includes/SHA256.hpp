#pragma once

#include <string>

std::string generate_sha256(const std::string&);
bool sha256_match(const std::string&, const std::string&);
