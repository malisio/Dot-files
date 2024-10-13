#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
  unsigned int seed;
  
  FILE * fptr;
  fptr=fopen("./flag.enc","rb");
  if(fptr == NULL){
    perror("can't open file");
    return -1;
  }
  fread(&seed,1,4,fptr);

  fseek(fptr,0,SEEK_END);
  size_t size = ftell(fptr);
  fseek(fptr,0,SEEK_SET);

  unsigned char * flag = (char *) malloc(size);
  fread(flag,1,size,fptr);
  fclose(fptr);
  
  srand(seed);
  int enc1=0,enc2=0;
 
  for(long i = 4 ; i < (long)size; i ++){
    enc1= rand();
    enc2= rand();
    enc2 = enc2 & 7;
    flag[i]= flag[i] >> enc2 | flag[i] << 8 -enc2;
    flag[i] = enc1 ^ flag[i];
    printf("%c",flag[i]);
  }
  return 0;
}
