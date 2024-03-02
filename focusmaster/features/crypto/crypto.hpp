#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <openssl/aes.h>
#include <openssl/rand.h>
#include "../../libs/base64/base64.h"

#pragma comment(lib, "libcrypto.lib")

class crypto {

public:
	std::string encrypt(std::string plaintext, std::string key, std::string iv);
	std::string decrypt(std::string ciphertext, std::string key, std::string iv);
	std::string generateIV();
	std::string encryptEncode(std::string plaintext, std::string key, std::string iv);
	std::string decryptDecode(std::string ciphertext, std::string key, std::string iv);
};