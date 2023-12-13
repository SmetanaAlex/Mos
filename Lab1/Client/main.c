#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>


#define IP "127.0.0.1"
#define MY_ERROR 1
#define PORT 7777
#define MAX_SERVER_MSG_LEN 20000

int main()
{
    WSADATA wsa;
    SOCKET mySocket;
    struct sockaddr_in server;
    int sockAddrInLength = sizeof(struct sockaddr_in);
    char serverMessage[MAX_SERVER_MSG_LEN];
    int serverMessageLength;

    if(WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        fprintf(stderr, "WSAStartup failed.\n");
        getchar();
        return MY_ERROR;
    }
    printf("WSASucceeded.\n");

    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);



    char* message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi elit turpis, tempus a fermentum non, "
                    "aliquet at velit. Nunc ornare sagittis odio sit amet ultricies. Nulla convallis, dolor id varius lobortis,"
                    "eros erat finibus ante, quis rhoncus leo tellus at leo. Curabitur non interdum purus. Vivamus mollis leo sapien."
                    "Nullam laoreet enim quis interdum pharetra. Nam risus mi, pretium non est in, maximus ultrices neque. Fusce eu vehicula"
                    "dui. Cras risus risus, porta vel lorem vitae, tristique lobortis eros. Mauris ultricies vel quam placerat eleifend."
                    "Cras ac ornare arcu, commodo feugiat quam. Proin sed egestas leo, in sodales mi."
                    "Aliquam molestie ac ex a sollicitudin. Fusce id metus non lorem interdum malesuada. Donec at aliquet lacus"
                    ", eu volutpat nulla. Phasellus varius semper magna. Phasellus gravida ipsum non bibendum posuere."
                    "Nulla vel justo id erat rhoncus finibus eget nec nulla. Proin in arcu nibh."
                    "Duis quis suscipit arcu, et tincidunt felis. Donec a est rhoncus, tincidunt lectus pretium, consequat justo."
                    "Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. "
                    "Curabitur in quam vitae tellus gravida ultrices non eget lacus. Aenean convallis eros a varius consequat."
                    "Nunc interdum ante eu consequat auctor. Aliquam erat volutpat. Mauris sit amet enim magna."
                    "Donec lobortis, ex at volutpat tristique, libero neque accumsan mi, nec varius ex justo ac sapien."
                    "Duis condimentum arcu non accumsan ullamcorper. Curabitur in felis sem."
                    "Fusce massa odio, dictum sed varius sed, vehicula at velit."
                    "Mauris eget posuere ante. Ut facilisis arcu finibus mi interdum dapibus in non libero."
                    "Phasellus iaculis magna quam, non cursus nibh mollis et. Pellentesque habitant morbi tristique senectus et netus"
                    "et malesuada fames ac turpis egestas. Fusce eu dictum nisi, id aliquet lectus. Ut sem libero, sollicitudin sit amet"
                    "neque vel, accumsan congue nulla. Nullam commodo felis dui, vitae consequat enim dictum at."
                    "Pellentesque id metus eget mauris dignissim lacinia. Vivamus aliquam ligula sed molestie volutpat."
                    "Maecenas dapibus ut nisl vitae sodales. Etiam placerat sed mauris eu congue. Duis ac odio quam. "
                    "Nam sagittis sem vitae ante euismod, at aliquet augue egestas. Praesent nec hendrerit urna."
                    "Nam at posuere justo. Cras et mi sapien."
                    "Praesent vehicula sem sed nibh faucibus consectetur. Vivamus sed diam eu arcu molestie tempor vel in nibh."
                    "Vivamus eget dapibus tortor, sit amet tincidunt neque. Aenean posuere convallis maximus."
                    " Donec aliquet urna ac sem congue, non pulvinar elit porta. Duis convallis ac mi at euismod. "
                    "Vestibulum facilisis ipsum at ex auctor euismod. Quisque bibendum purus eu iaculis feugiat."
                    "Pellentesque eu volutpat velit. Pellentesque pharetra, enim eu porta hendrerit, lorem enim consectetur urna, "
                    "vel scelerisque libero magna at lacus.";




    mySocket = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);

    if (mySocket == INVALID_SOCKET)
    {
        fprintf(stderr, "Socket creation failed.\n");
        getchar();
        return MY_ERROR;
    }

    if (connect(mySocket, (struct sockaddr*) &server, sizeof server) < 0)
    {
        fprintf(stderr, "Connection failed. error: %d\n",WSAGetLastError());
        getchar();
        return MY_ERROR;
    }
    printf("Connection established.\n");

    for (int i=0; i<100000; i++)
    {
        if (send(mySocket, message, strlen(message), 0) < 0)
        {
            fprintf(stderr, "Sending failed.\n");
            return MY_ERROR;
        }
        printf("Sending succeeded.\n");

    }

    closesocket(mySocket);
    getchar();
    return 0;
}
