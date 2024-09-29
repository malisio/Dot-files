#include <stdio.h>
#include <stdlib.h>


// It returns (base^exponent) % mod
long long int modular_exponentiation(long long int base, long long int exponent, long long int mod) {
    long long int result = 1;
    base = base % mod; 
    
    while (exponent > 0) {
      
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
     
        exponent = exponent >> 1;
        base = (base * base) % mod;  
    }
    return result;
}

