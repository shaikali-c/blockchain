#pragma once
#include <pch/pch.h>
#include <sodium/utils.h>
#include <leveldb/db.h>
#include <leveldb/options.h>
#include <leveldb/status.h>

std::string toHex(const std::vector<unsigned char>);
void createDirectory(const std::string& path);

void save(const std::string& key, const std::string& value, const std::string& dbName = "keys");
std::string load(const std::string& key, const std::string& dbName = "keys");
