#include <cryptography/common.h>

std::string toHex(const std::vector<unsigned char> key) {
    std::string hex(key.size() * 2 + 1, '\0');
    sodium_bin2hex(&hex[0], hex.size(), key.data(), key.size());
    hex.pop_back();
    return hex;
}

void save(const std::string& key, const std::string& value, const std::string& dbName) {
    auto& manager = DBManager::getInstance(dbName);
    leveldb::DB* db = manager.getDB();
    db->Put(leveldb::WriteOptions(), key, value);

}
std::string load(const std::string& key, const std::string& dbName) {
    auto& manager = DBManager::getInstance(dbName);
    leveldb::DB* db = manager.getDB();

    std::string value;
    db->Get(leveldb::ReadOptions(), key, &value);
    return value;
}

std::string hash_stream(std::stringstream& ss)
{
    std::string data = ss.str();

    unsigned char hash[crypto_generichash_BYTES];

    crypto_generichash(
        hash,
        sizeof(hash),
        reinterpret_cast<const unsigned char*>(data.data()),
        data.size(),
        NULL,
        0
    );

    std::stringstream hex;
    for (size_t i = 0; i < sizeof(hash); i++)
        hex << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return hex.str();
}
