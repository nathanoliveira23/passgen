#pragma once

#include <cstdlib>
#include <string>

const std::string TEMPFILE      = "/tmp/passgenDB.txt";
const std::string ENCFILE       = static_cast<std::string>(getenv("HOME")).append("/passgenDB.txt.enc");
const std::string SECKEYFILE    = static_cast<std::string>(getenv("HOME")).append("/secret.key");
