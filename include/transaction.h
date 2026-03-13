#include <pch/pch.h>

struct Input {

    std::string transaction_hash;
    uint8_t output_index;
    std::vector<unsigned char> signature;

    std::string getInput() const {
        return transaction_hash + std::to_string(output_index);
    }
};

struct Output {
    std::string publicKey;
    uint64_t coins;
};

class Transaction {
    std::vector<Input> inputs;
    std::vector<Output> outputs;

    uint64_t coins;
};
