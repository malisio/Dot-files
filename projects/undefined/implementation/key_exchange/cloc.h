#include <stdio.h>
#include <stdlib.h>
#define PORT 1337 
#define IP "0.0.0.0"

int xigor(int a, int b) {
    int ret = 1;
    for (int i = 0; i < b; i++) { // Correct loop
        ret *= a;
    }
    return ret;
}


long long int mod_exp(long long int base, long long int exp, long long int mod) {
    long long int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod;
    }
    return result;
}

long long int algo(long long int base, long long int exp, long long int mod) {
    return mod_exp(base, exp, mod);
}
