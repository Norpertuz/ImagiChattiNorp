
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <functions.h>
#define MAX_MESSAGE_SIZE 1024

struct ClientMessage{
        char username[100];
        char text[MAX_MESSAGE_SIZE];
};


int main(){
        int clientSocket;
        struct sockaddr_in serverAddr;
        struct ClientMessage message;

        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1){
                perror("Error during initialization of client socket!");
                exit(1);
        }

        //Server address config
        serverAddr.sin_family = AF_INET;

        //Server address config
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(12345);
        serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        //connect to the server
        if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
                perror("Connection Error");
                close(clientSocket);
                exit(1);
        }

        printf("Enter your nickname: ");
        scanf("%s", message.username);
        printf("Enter your message: ");
        scanf("%s", message.text);

        if(send(clientSocket, &message, sizeof(message), 0) == -1){
                perror("Can't send message");
        }

        close(clientSocket);

        return 0;
}
