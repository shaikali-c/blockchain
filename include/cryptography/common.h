#pragma once
#include "db.h"
#include <pch/pch.h>
#include <sodium/utils.h>
#include <sodium.h>

std::string toHex(const std::vector<unsigned char>);
void createDirectory(const std::string& path);
std::string hash_stream(std::stringstream& ss);

void save(const std::string& key, const std::string& value, const std::string& dbName = "keys");
std::string load(const std::string& key, const std::string& dbName = "keys");
