#include <transaction.h>

Transaction::Transaction(const std::string& s, const std::string& r, uint64_t c, const std::vector<Input>& i, const std::vector<Output>& o) : inputs(i), outputs(o), sender(s), reciever(r), coins(c) {
    std::stringstream base;
    base << sender << reciever << coins;

    for(size_t i = 0; i < inputs.size(); i++) {
        base << inputs[i].getInput();
    }

    for(size_t i = 0; i < outputs.size(); i++) {
        base << outputs[i].public_key << outputs[i].coins;
    }
    transaction_hash = hash_stream(base);
    std::cout << transaction_hash << "\n";
}
