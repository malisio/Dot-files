#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void set_root(void){
    setuid(0);
    setgid(0);
    exec("/bin/sh");
}

int main(){

    char buf[1024];
    fgets(buf,200,stdin);

    printf("Ping seadris in discord to get answer\n ");

    return 0;
}