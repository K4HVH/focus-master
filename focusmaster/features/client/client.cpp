#include "client.hpp"

crypto cr;
http ht;

void client::debugtest() {
    // Plain text message to encrypt
    std::string plainText = "Hello, this is a secret message.";

    std::string iv = cr.generateIV();

    // Encrypt the message using AES
    std::string encryptedText = cr.encrypt(plainText, key, iv);

    auto encodedText = base64_encode(encryptedText);

    json msg;
    msg["iv"] = iv;
    msg["encryptedText"] = encodedText;

    std::string jsonString = msg.dump(); // Serialize the JSON object to a string

    auto response = json::parse(ht.postReq(jsonString, L"/decrypt", true));

    // Extract the data and iv values
    std::string data = response["data"];
    std::string respIV = response["iv"];

    std::cout << data << std::endl;
    std::cout << respIV << std::endl;

    if (data != "Dunno") {
        std::cout << cr.decrypt(base64_decode(data), key, respIV) << std::endl;
    }

    return;
}

std::string client::generateKey(int length) {
    std::string iv = cr.generateIV();
    std::string encodedMK = cr.encryptEncode(masterkey, key, iv);
    std::string encodedLength = cr.encryptEncode(std::to_string(length), key, iv);

    json msg;
    msg["iv"] = iv;
    msg["mk"] = encodedMK;
    msg["length"] = encodedLength;

    std::string jsonString = msg.dump(); // Serialize the JSON object to a string

    auto response = json::parse(ht.postReq(jsonString, L"/generate", true));

    std::string data = response["data"];
    std::string respIV = response["iv"];

    std::string license = cr.decrypt(base64_decode(data), key, respIV);

    return license;
}