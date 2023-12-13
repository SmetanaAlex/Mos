#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <time.h>

#define MY_ERROR 1
#define PORT 7777
#define MAX_NUM_CLIENTS 1
#define MAX_CLIENT_MSG_LEN 20000

int main()
{
    WSADATA wsa;
    SOCKET mySocket, acceptSocket;
    struct sockaddr_in server, client;
    int sockAddrInLength = sizeof(struct sockaddr_in);
    char clientMessage[MAX_CLIENT_MSG_LEN];
    int clientMessageLength = 1;
    char* message;
    clock_t start;
    int sizeMess = 0;
    int a = 1;

    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        fprintf(stderr, "WSAStartup failed.\n");
        return MY_ERROR;
    }
    printf("WSAStartup succeded.\n");

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (mySocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed.\n");
        return MY_ERROR;
    }
    printf("Socket creation succeeded.\n");

    if (bind(mySocket, (struct sockaddr*) &server, sizeof server) == SOCKET_ERROR)
    {
        fprintf(stderr, "Binding socket on port %d failed.\n", PORT);
        return MY_ERROR;
    }
    printf("Binding socket on port %d successfully.\n", PORT);

    listen(mySocket, MAX_NUM_CLIENTS);
    printf("Waiting for a connection...\n");

    acceptSocket = accept(mySocket, (struct sockaddr*) &client, &sockAddrInLength);
    if (acceptSocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Accept failed.\n");
        return MY_ERROR;
    }
    printf("Accept succeeded.\n");

    start = clock();

    while (clientMessageLength > 0)
    {
        clientMessageLength = recv(acceptSocket, clientMessage, sizeof clientMessage, 0);
        if (clientMessageLength == 0) break;
        if (clientMessageLength == SOCKET_ERROR)
        {
            fprintf(stderr, "Recv failed.\n");
            return MY_ERROR;
        }
        clientMessage[clientMessageLength] = '\0';
        //printf("%s\n", clientMessage);
        sizeMess += strlen(clientMessage);
/*
        message = "Server response";
        if (send(acceptSocket, message, strlen(message), 0) < 0)
        {
            fprintf(stderr, "Send failed.\n");
            return MY_ERROR;
        }
        //printf("Send succeded.\n\n");
        */
    }

    printf("Took %f seconds.\n", ((double)(clock() - start))/CLOCKS_PER_SEC);
    printf("Total size: %d bytes\n", sizeMess);

    closesocket(mySocket);
    WSACleanup();
    getchar();
    return 0;
}
