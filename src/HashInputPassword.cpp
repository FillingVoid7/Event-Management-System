#include "HashInputPassword.h"
#include <sodium.h>
#include <stdexcept>

std::string hashInputPassword(const std::string& password) {
    if (sodium_init() < 0) {
        throw std::runtime_error("Failed to initialize sodium");
    }

    std::string hashedPassword(crypto_pwhash_STRBYTES, '\0');
    if (crypto_pwhash_str(reinterpret_cast<char*>(&hashedPassword[0]), password.c_str(),
                          password.length(), crypto_pwhash_OPSLIMIT_INTERACTIVE,
                          crypto_pwhash_MEMLIMIT_INTERACTIVE) != 0) {
        throw std::runtime_error("Failed to hash password");
    }

    return hashedPassword;
}
