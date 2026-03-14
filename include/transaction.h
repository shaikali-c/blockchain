#pragma once

#include <pch/pch.h>
#include <cryptography/common.h>
#include <sodium.h>

struct Input {
    std::string transaction_hash;
    uint8_t output_index;
    std::vector<unsigned char> signature;

    std::string getInput() const {
        return transaction_hash + std::to_string(output_index);
    }
};

struct Output {
    std::string public_key;
    uint64_t coins;
};

class Transaction {
    std::vector<Input> inputs;
    std::vector<Output> outputs;
    uint64_t coins;
    std::string sender, reciever, transaction_hash;
    public:
        Transaction(const std::string& s, const std::string& r, uint64_t c, const std::vector<Input>& i, const std::vector<Output>& o);
};
