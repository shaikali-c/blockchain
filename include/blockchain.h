#pragma once
#include <pch/pch.h>

class Transaction;
class UTXO;
class Block;

class Blockchain{
    public:
        std::unordered_map<std::string, Transaction> transactions;
        std::unordered_map<std::string, UTXO> utxo;
        std::vector<Block> blocks;
};
