#pragma once

#include <string>
#include <array>
#include <openssl/sha.h>
#include "../includes/types.h"

std::array<byte, SHA256_DIGEST_LENGTH> generate_sha256(const std::string&);
bool sha256_match(const std::string&, std::array<byte, SHA256_DIGEST_LENGTH>);
