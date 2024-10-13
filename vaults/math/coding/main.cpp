#include <iostream>
#include <string>
#include <cstring>


int check_op(char );

int main(){
  int x;
  std::string s;
  std::cin>>s;
  std::cin>>x;
  
  int x_position[1024]={0};
  int current=0;


  int array[10];
  current = 0 ; 
  int tot=0,tmp=0;
  char new_string[1024];
  char tmp_string[1024]; 

  for(int i = 0 ; i < s.length() ; i++,current++){
    if(!check_op(s[i]) && s[i]!= 'x' ){
         tmp_string[i] = s[i];
    }
    else if(check_op(s[i]) || s[i] == 'x'){
      tmp_string[i]=' ';
    }
  }
  int num = atoi(tmp_string);

  std::cout<<"Number: "<<num<<std::endl;
  std::cout<<"Tmp str "<<tmp_string<<std::endl;

  return 0;
}


int check_op(char s){

  if(s == '+' || s == '-' || s == '*' || s == '^'){
    return s;
  }
  return 0;
}
