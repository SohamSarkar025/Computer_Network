//ASSG9
//Concurrent Echo Server TCP


//Client(A)

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define CLIENT_IP "127.0.0.2"
#define CLIENT_PORT 5981
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5980
void main()
{
        struct sockaddr_in client, server;
        int sd;
        char msg[512], msg1[512];
        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        bzero((char*)&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(CLIENT_PORT);
        client.sin_addr.s_addr = inet_addr(CLIENT_IP);
        sd = socket(AF_INET, SOCK_STREAM, 0);
        connect(sd, (struct sockaddr*)&server, sizeof(server));
        do
        {
                printf("Enter a Message: ");
                scanf("%s", msg);
                send(sd, msg, strlen(msg)+1, 0);
                memset(msg1, 0x0, 512);
                recv(sd, msg1, 512, 0);
                printf("\nMessage received from Server: %s\n", msg1);
        }while(strcmp(msg, "stop"));
        close(sd);
}

//Client(B)

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define CLIENT_IP "127.0.0.3"
#define CLIENT_PORT 5982
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5980
void main()
{
        struct sockaddr_in client, server;
        int sd;
        char msg[512], msg1[512];
        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        bzero((char*)&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(CLIENT_PORT);
        client.sin_addr.s_addr = inet_addr(CLIENT_IP);
        sd = socket(AF_INET, SOCK_STREAM, 0);
        connect(sd, (struct sockaddr*)&server, sizeof(server));
        do
        {
                printf("Enter a Message: ");
                scanf("%s", msg);
                send(sd, msg, strlen(msg)+1, 0);
                memset(msg1, 0x0, 512);
                recv(sd, msg1, 512, 0);
                printf("\nMessage received from Server: %s\n", msg1);
        }while(strcmp(msg, "stop"));
        close(sd);
}


//Server

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5980
void main()
{
        struct sockaddr_in client, server;
        int pid, sd, nsd, clen = sizeof(client);
        char msg[512];
        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        sd = socket(AF_INET, SOCK_STREAM, 0);
        bind(sd, (struct sockaddr*)&server, sizeof(server));
        listen(sd, 5);
        while(1)
        {
                nsd = accept(sd, (struct sockaddr*)&client, &clen);
                pid = fork();
                if(pid < 0)
                {
                        printf("Error in fork()");
                        exit(0);
                }
                else if(pid > 0)
                {
                        close(nsd);
                }
                else
                {
                        do
                        {
                                memset(msg, 0x0, 512);
                                recv(nsd, msg, 512, 0);
                                send(nsd, msg, strlen(msg)+1, 0);
                        }while(strcmp(msg, "stop"));
                }
        }
}
