#pragma once

#include <pch/pch.h>
#include <sodium.h>
#include <cryptography/common.h>
#include <sodium/crypto_sign.h>
#include <vector>

class Keys {
  private:
    std::string master;
    std::vector<unsigned char> _secretKey;
    std::vector<unsigned char> _publicKey;
    void createKeys();
  public:
    Keys();
    Keys(const std::string&);
    const std::vector<unsigned char>& publicKey() const;
    const std::vector<unsigned char>& secretKey() const;

    const std::string publicKeyHex() const;
    const std::string secretKeyHex() const;

    void saveKeys(const std::string&);
    void loadKeys(const std::string&);

    std::vector<unsigned char> sign(const std::string&);
    int verifySignature(const std::string&, std::vector<unsigned char>);

};
