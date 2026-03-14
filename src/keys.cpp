#include <cryptography/keys.h>

Keys::Keys(){
    addr.resize(32);
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

void Keys::saveKeys(const std::string& kname) {

    const size_t secKeySize = crypto_sign_SECRETKEYBYTES;
    const size_t pubKeySize = crypto_sign_PUBLICKEYBYTES;

    std::stringstream base;

    base.write(reinterpret_cast<const char*>(&secKeySize), sizeof(secKeySize));
    base.write(reinterpret_cast<const char*>(_secretKey.data()), _secretKey.size());
    base.write(reinterpret_cast<const char*>(&pubKeySize), sizeof(pubKeySize));
    base.write(reinterpret_cast<const char*>(_publicKey.data()), _publicKey.size());

    std::string serialize = base.str();
    save(kname, serialize);

}

void Keys::deserializeKeys(const std::string& data) {

    const size_t secKeySize = crypto_sign_SECRETKEYBYTES;
    const size_t pubKeySize = crypto_sign_PUBLICKEYBYTES;

    size_t pos = 0;
    size_t size1;
    memcpy(&size1, data.data() + pos, sizeof(size1));
    pos += sizeof(size1);
    _secretKey.assign(reinterpret_cast<const unsigned char*>(data.data() + pos),reinterpret_cast<const unsigned char*>(data.data() + pos + size1));
    pos += size1;
    size_t size2;
    memcpy(&size2, data.data() + pos, sizeof(size2));
    pos += sizeof(size2);
    _publicKey.assign(reinterpret_cast<const unsigned char*>(data.data() + pos),reinterpret_cast<const unsigned char*>(data.data() + pos+ size2));
}

void Keys::loadKeys(const std::string& kname) {

    std::string serializedKeys = load(kname);
    deserializeKeys(serializedKeys);

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

int Keys::verifySignature(const std::string& base, const std::vector<unsigned char>& signature) {
    int result = crypto_sign_verify_detached(
            signature.data(),
            (unsigned char*)base.data(),
            base.size(),
            _publicKey.data()
        );
    return result;
}
