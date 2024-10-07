#include <iostream>
#include <math.h>

bool isprime(int num){
    if(num == 1){
      return false;
    }

    for(int i = sqrt(num) ; i < num ; i++){
      if(num % i == 0){
        return false;
      }
    }
    return true;
}

int main(){

  int t = 997;

  if(isprime(t)){
    std::cout<<"Yes"<<std::endl;
  }
  else{
    std::cout << "NO\n";
  }

}
