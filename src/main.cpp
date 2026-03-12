#include <cryptography/keys.h>
#include <sodium.h>

int main() {
    if (sodium_init() < 0) {
        return 1;
    }
    Keys mykeys{"shaiks"};
}
