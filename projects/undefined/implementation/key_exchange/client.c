#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "cloc.h"
#define PORT 1337

int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
    int private = 4;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }
    valread= read(client_fd,buffer,sizeof(buffer));
    printf("%s",buffer);
   
    int G = 5 ;

   
    int P = 23;

    int Public_key = algo(G,private,P);
    printf("[*]--- My Public key %d ---[*]\n",Public_key);
    char str[128];
    sprintf(str,"%d",Public_key);
    send(client_fd,str,strlen(str),0);
    
    valread = read(client_fd,buffer,sizeof(buffer));

    int Server_Public_key = atoi(buffer);
    printf("Server Public key :%d\n",Server_Public_key);
    int Private_key = algo(G,private,Server_Public_key);
   
    printf("My private key: %d\n", Private_key);
    sprintf(str,"%d",Private_key);

    send(client_fd,str,strlen(str),0);
    // closing the connected socket
    close(client_fd);
    return 0;

}
