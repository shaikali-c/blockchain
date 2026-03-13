#include <cryptography/common.h>

namespace fs = std::filesystem;

std::string toHex(const std::vector<unsigned char> key) {
    std::string hex(key.size() * 2 + 1, '\0');
    sodium_bin2hex(&hex[0], hex.size(), key.data(), key.size());
    hex.pop_back();
    return hex;
}

void save(const std::string& key, const std::string& value, const std::string& dbName) {

    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, dbName, &db);

    if(!status.ok()) {
        std::cerr << "Bad!" << status.ToString() << "\n";
        return;
    }

    status = db->Put(leveldb::WriteOptions(), key, value);

}
std::string load(const std::string& key, const std::string& dbName) {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, dbName, &db);

    if(!status.ok()) {
        std::cerr << "Bad!" << status.ToString() << "\n";
        return "";
    }

    std::string value;
    status = db->Get(leveldb::ReadOptions(), key, &value);
    return value;
}


void createDirectory(const std::string& path) {
    if (!fs::exists(path)) {
        if (fs::create_directory(path)) {
            std::cout << "Directory created: " << path << '\n';
        } else {
            throw std::runtime_error("Failed to create directory: " + path);
        }
    }
}
