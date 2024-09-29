#include <stdio.h>
#include <math.h>
#include "header.h"

long long int power(long long int a, long long int b,
                    long long int P){

  if(b == 1){
    return a;
  }
  else {

    return (((long long int)xigor(a,b)) %P);

  }

}


int main(){

  /*Both parties should have this two Numbers*/
   long long int P = 23 ;
   long long int G = 5 ;
  
  /*Those are the secret keys they dont need to be exchanged*/
   long long int Secret1 = 1337;
   long long int Secret2 = 7;

  /*Generate keys that are going to be exchanged*/

  long long int x =  power(G,Secret1,P);
  long long int y =  power(G,Secret2,P);

  /*Private keys*/
  long long int Key1 = power(y,Secret1,P);
  long long int Key2 = power(x,Secret2,P);

  printf("Key1: %lld\n",Key1);
  printf("Key2: %lld\n",Key2);
  printf("\n");
  return 0;
}
