#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "cloc.h"
#include <string.h>

char buffer[64];

int main(){
  
  struct sockaddr_in serv_address;
  int socketfd,opt=1;
  const char * data = "Hello Let agree on two Number\n";
  socketfd = socket(AF_INET,SOCK_STREAM,0);
  if(socketfd < 0){
    printf("socket creating err\n");
    exit(EXIT_FAILURE);
  }
  
if (setsockopt(socketfd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        printf("setsockopt\n");
        exit(EXIT_FAILURE);
    }


  serv_address.sin_family = AF_INET;
  serv_address.sin_port = htons(PORT);
  


  serv_address.sin_addr.s_addr= INADDR_ANY;
  int serv_len =sizeof(serv_address);
  if(bind(socketfd,(const struct sockaddr*)&serv_address,serv_len) < 0 ){
    printf("Binding error\n");
     close(socketfd);
    exit(EXIT_FAILURE);
  }
  
  if(listen(socketfd,3) < 0){
    printf("listening err\n");
    close(socketfd);
    exit(EXIT_FAILURE);
  }
    int new_socket;
    if ((new_socket = accept(socketfd, (struct sockaddr *)&serv_address, (socklen_t*)&serv_len)) < 0) {
        printf("accept error for god damn fuck sake\n");
        return 1;
    }

  if(send(new_socket,data,strlen(data),0) < 0){

    printf("Take a fucking break\n");
    return 1;
  }

  //printf("Data sent!\n");
  /*
  int valread =  read(new_socket,buffer,sizeof(buffer)-1);
  if(valread < 0 ){
    printf("go sleep\n");
  }

  
  int P = atoi(buffer);
  valread = read(new_socket, buffer, sizeof(buffer)-1);
  int G = atoi(buffer);
  if(valread < 0 ) {
    printf("I'm fucked\n");
    return 1;
  }
*/
  int P = 23;
  int G = 5;
  int private = 4;
  printf("P: %d G:%d\n",P,G);
  
  int Public_key = algo(G,private,P);

  read(new_socket, buffer, sizeof(buffer)-1);

  int Client_Public_key = atoi(buffer);

  printf("Client Public Key :%d\nMy Public key %d \n", Client_Public_key,Public_key);

  sprintf(buffer,"%d",Public_key);
  send(new_socket,buffer,strlen(buffer),0);
  
  read(new_socket , buffer, sizeof(buffer)-1);
  
  int Private_key = algo(G,private,Client_Public_key);
  int Client_private_key = atoi(buffer);
  printf("Client Private key %d\nSever Private key %d",Client_private_key,Private_key);
  close(socketfd);
  close(new_socket);
  return 0;
}
