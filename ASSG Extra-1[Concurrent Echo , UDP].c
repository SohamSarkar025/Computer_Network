//ASSG Extra-1
//
//Client-1

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define CLIENT_IP "127.0.0.2"
#define CLIENT_PORT 6545
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6550
void main()
{
        struct sockaddr_in client, server;
        int sd,slen=sizeof(server);
        char msg[512], msg1[512];

        bzero((char*)&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(CLIENT_PORT);
        client.sin_addr.s_addr = inet_addr(CLIENT_IP);
        
        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = inet_addr(SERVER_IP);

        sd = socket(AF_INET, SOCK_DGRAM, 0);

        bind(sd, (struct sockaddr*)&client, sizeof(client));
        do
        {
                printf("Enter a Message: ");
                scanf("%s", msg);
                sendto(sd, msg, strlen(msg)+1,0,(struct sockaddr*)&server,sizeof(server));
                memset(msg1, 0x0, 512);
                recvfrom(sd, msg1, 512, 0,(struct sockaddr*)&server,&slen);
                printf("\nMessage received from Server: %s\n", msg1);
        }while(strcmp(msg, "stop"));
        close(sd);
}

//Client-2

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define CLIENT_IP "127.0.0.3"
#define CLIENT_PORT 6546
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6550
void main()
{
        struct sockaddr_in client, server;
        int sd,slen=sizeof(server);
        char msg[512], msg1[512];

        bzero((char*)&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(CLIENT_PORT);
        client.sin_addr.s_addr = inet_addr(CLIENT_IP);
        
        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = inet_addr(SERVER_IP);

        sd = socket(AF_INET, SOCK_DGRAM, 0);

        bind(sd, (struct sockaddr*)&client, sizeof(client));
        do
        {
                printf("Enter a Message: ");
                scanf("%s", msg);
                sendto(sd, msg, strlen(msg)+1,0,(struct sockaddr*)&server,sizeof(server));
                memset(msg1, 0x0, 512);
                recvfrom(sd, msg1, 512, 0,(struct sockaddr*)&server,&slen);
                printf("\nMessage received from Server: %s\n", msg1);
        }while(strcmp(msg, "stop"));
        close(sd);
}

//server
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6550
void main()
{
        struct sockaddr_in client, server;
        int pid, sd, nsd, clen = sizeof(client);
        char msg[512];
        
        bzero((char*)&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        
        sd = socket(AF_INET, SOCK_DGRAM, 0);
        bind(sd, (struct sockaddr*)&server, sizeof(server));
 
        while(1){
            do
            {
                   memset(msg,0x0,512);
                   recvfrom(sd,msg,512,0,(struct sockaddr*)&client,&clen);
                   sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&client,clen);
            }while(strcmp(msg,"stop"));
        }
}