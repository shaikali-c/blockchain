#include <transaction.h>
#include <sodium.h>

int main() {
    if (sodium_init() < 0) {
        return 1;
    }
    Transaction tx{"MARWAAN", "AASIA", 400, {}, {}};
}
