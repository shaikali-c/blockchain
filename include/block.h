#pragma once
#include <pch/pch.h>
#include <transaction.h>

class BlockHeader {
    protected:
        std::string block_hash, prev_hash, merkle_root;
        uint64_t nonce, timestamp;
        BlockHeader(const std::string& bh, const std::string& ph, const std::string& mr, uint64_t n, uint64_t t) :
            block_hash(bh), prev_hash(ph), merkle_root(mr), nonce(n), timestamp(t){}
};

class Block : public BlockHeader {
    private:
        std::vector<Transaction> transactions;
        uint64_t block_height;
    public:
        Block()  : BlockHeader("", "", "", 0, 0) {}
        void setBlockHash(const std::string&);
        void setPrevHash(const std::string&);
        void setTimestamp(uint64_t);
        void setNonce(uint64_t);
        void setMerkleRoot(const std::string&);
        void addTransaction(const Transaction&);
};
