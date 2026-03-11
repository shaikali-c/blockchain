#include <cryptography/common.h>

namespace fs = std::filesystem;

std::string toHex(const std::vector<unsigned char> key) {
    std::string hex(key.size() * 2 + 1, '\0');
    sodium_bin2hex(&hex[0], hex.size(), key.data(), key.size());
    hex.pop_back();
    return hex;
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
