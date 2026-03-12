#include <cryptography/keys.h>
#include <sodium/crypto_sign.h>

Keys::Keys(){
    createKeys();
}
Keys::Keys(const std::string& kname){
    _secretKey.resize(crypto_sign_SECRETKEYBYTES);
    _publicKey.resize(crypto_sign_PUBLICKEYBYTES);
    loadKeys(kname);
};

void Keys::createKeys() {
    _secretKey.resize(crypto_sign_SECRETKEYBYTES);
    _publicKey.resize(crypto_sign_PUBLICKEYBYTES);
    crypto_sign_keypair(_publicKey.data(), _secretKey.data());
}

const std::vector<unsigned char>& Keys::publicKey() const {
    return _publicKey;
}

const std::vector<unsigned char>& Keys::secretKey() const {
    return _secretKey;
}

const std::string Keys::publicKeyHex() const {
    return toHex(_publicKey);
}
const std::string Keys::secretKeyHex() const {
    return toHex(_secretKey);
}

void Keys::saveKeys(const std::string& filename) {

    createDirectory(filename);
    std::ofstream sk_file(filename + "/secret.k", std::ios::binary);
    std::ofstream pk_file(filename + "/public.k", std::ios::binary);

    if (!sk_file || !sk_file) throw std::runtime_error("Cannot open files for writing");

    sk_file.write(reinterpret_cast<const char*>(_secretKey.data()), _secretKey.size());
    pk_file.write(reinterpret_cast<const char*>(_publicKey.data()), _publicKey.size());
}

void Keys::loadKeys(const std::string& kname) {
    std::ifstream secretKey(kname + "/secret.k", std::ios::binary);
    std::ifstream publicKey(kname + "/public.k", std::ios::binary);

    secretKey.read(reinterpret_cast<char*>(_secretKey.data()), crypto_sign_SECRETKEYBYTES);
    publicKey.read(reinterpret_cast<char*>(_publicKey.data()), crypto_sign_PUBLICKEYBYTES);
}

std::vector<unsigned char> Keys::sign(const std::string& base) {
    std::vector<unsigned char> signature(crypto_sign_BYTES);

    crypto_sign_detached(
        signature.data(),
        nullptr,
        reinterpret_cast<const unsigned char*>(base.data()),
        base.size(),
        _secretKey.data()
    );

    return signature;
}

int Keys::verifySignature(const std::string& base, std::vector<unsigned char> signature) {
    int result = crypto_sign_verify_detached(
            signature.data(),
            (unsigned char*)base.data(),
            base.size(),
            _publicKey.data()
        );
    return result;
}
