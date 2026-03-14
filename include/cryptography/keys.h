#pragma once

#include <pch/pch.h>
#include <sodium.h>
#include <db.h>
#include <cryptography/common.h>

class Keys {
  private:
    std::string master;
    std::vector<unsigned char> _secretKey;
    std::vector<unsigned char> _publicKey;
    std::vector<uint8_t> addr;

    void createKeys();
    void deserializeKeys(const std::string&);
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
    int verifySignature(const std::string&, const std::vector<unsigned char>&);

};
