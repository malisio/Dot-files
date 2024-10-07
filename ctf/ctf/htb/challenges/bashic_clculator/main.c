#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#define PORT 1337
#define BUFFER_SIZE 1024

void *minConnection(void *arg);
void *handleConnection(void *arg);
void executeCommand(const char *cmd, char *output, size_t outputSize);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    printf("Starting tcp server on 0.0.0.0:%d\n", PORT);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            continue;
        }

        printf("Client %s connected.\n", inet_ntoa(address.sin_addr));

        pthread_t thread1, thread2;
        pthread_create(&thread1, NULL, minConnection, (void *)(intptr_t)new_socket);
        pthread_create(&thread2, NULL, handleConnection, (void *)(intptr_t)new_socket);
    }

    return 0;
}

void *minConnection(void *arg) {
    int conn = (intptr_t)arg;
    sleep(600);
    close(conn);
    return NULL;
}

void executeCommand(const char *cmd, char *output, size_t outputSize) {
    FILE *fp;
    fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen failed");
        return;
    }
    fgets(output, outputSize, fp);
    pclose(fp);
}

void *handleConnection(void *arg) {
    int conn = (intptr_t)arg;
    char buffer[BUFFER_SIZE];
    char output[BUFFER_SIZE];

    send(conn, "CALCULATOR\n", strlen("CALCULATOR\n"), 0);

    while (1) {
        send(conn, "\nOperation: ", strlen("\nOperation: "), 0);
        ssize_t bytesRead = read(conn, buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0) {
            close(conn);
            return NULL;
        }
        buffer[bytesRead] = '\0';
        buffer[strcspn(buffer, "\n")] = 0; // Remove newline character

        char *firewall[] = {" ", "`", "$", "&", "|", ";", ">"};
        size_t opL1 = strlen(buffer);
        for (size_t i = 0; i < sizeof(firewall) / sizeof(firewall[0]); i++) {
            char *pos;
            while ((pos = strstr(buffer, firewall[i])) != NULL) {
                *pos = '\0';
                strcat(buffer, pos + 1);
                opL1--;
                send(conn, (char[50]){0}, sprintf((char[50]){0}, "%zu\t'%s' removed\n", 1, firewall[i]), 0);
            }
        }

        char command[BUFFER_SIZE];
        snprintf(command, sizeof(command), "echo $((%s))", buffer);
        executeCommand(command, output, sizeof(output));
        printf("%s: %s %s\n", inet_ntoa(((struct sockaddr_in *)&arg)->sin_addr), command, output);
        send(conn, output, strlen(output), 0);
    }
    return NULL;
}


