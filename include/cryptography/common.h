#pragma once
#include <pch/pch.h>
#include <sodium/utils.h>

std::string toHex(const std::vector<unsigned char>);
void createDirectory(const std::string& path);
