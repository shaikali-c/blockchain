#pragma once
#include <pch/pch.h>

class DBManager {
public:
    static DBManager& getInstance(const std::string& dbName);
    leveldb::DB* getDB();

    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

private:
    DBManager(const std::string& dbName);
    ~DBManager();
    leveldb::DB* db;
};
