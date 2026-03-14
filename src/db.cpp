#include <db.h>

DBManager& DBManager::getInstance(const std::string &dbName) {
    static DBManager instance(dbName);
    return instance;
}

DBManager::DBManager(const std::string& dbName) {
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, dbName, &db);
    if(!status.ok()) {
        std::cerr << "Failed to open Database Manager :(\n";
        db = nullptr;
    }
}

DBManager::~DBManager() {
    delete db;
}

leveldb::DB* DBManager::getDB(){
    return db;
}
