#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <stdio.h>

RSA *generate_key(){
  RSA *rsa = RSA_new();
  BIGNUM *bne = BIGNUM_new();
  if(bne == NULL || rsa == NULL){
    perror("rsa or bne null");
    return NULL;
  }
  if (BN_set_word(bne, RSA_F4) != 1) {
        perror("Error: Setting  bne");
        RSA_free(rsa);
        BIGNUM_free(bne);
        return NULL;
    }
  if(RSA_generate_key_ex(rsa,2048,bne,NULL) != 1){
    perror("Yeah skill issued by key");
    RSA_free(rsa);
    BIGNUM_free(bne);
    return NULL;
  }
  BIGNUM_free(bne);
  return rsa;
}



int main(){


  return 0;
}
