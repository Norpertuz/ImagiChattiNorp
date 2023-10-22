#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <functions.h>

#define MAX_
struct ClientMessage {
    char username[100];
    char text[1024];
};

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    struct ClientMessage message;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket initialization error");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // Port
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Every address will be accepted

    // bind server socket to address
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Binding error");
        close(serverSocket);
        exit(1);
    }

    // listening
    if (listen(serverSocket, 5) == -1) {
        perror("Listening error");
        close(serverSocket);
        exit(1);
    }

    printf("Waiting for connection...\n");

    //accepting connection
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        perror("Error: Accept error");
        close(serverSocket);
        exit(1);
    }

    printf("Connection Established.\n");

    //data receiving
    if (recv(clientSocket, &message, sizeof(message), 0) == -1) {
        perror("Error during message receiving");
    } else {
        printf("%s: %s\n",message.username, message.text);
	}
    return 0;
}
