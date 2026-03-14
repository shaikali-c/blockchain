#pragma once

#include <pch/pch.h>
#include <transaction.h>
#include <block.h>

class Blockchain{
    private:
        std::unordered_map<std::string, Transaction> transactions;
        std::unordered_map<std::string, Output> utxo;
        std::vector<Block> blocks;
    public:
        Blockchain();
};
