
//Iterative Day Time UDP
//ASSG8

//Client
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 6541
#define SERVER_IP "127.0.0.2"
#define SERVER_PORT 6540

void main(){
    struct sockaddr_in client,server;
    int sd,slen=sizeof(server);
    char msg[512],msg1[512];

    bzero((char *)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    bzero((char *)&client,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client.sin_port = htons(CLIENT_PORT);

    sd = socket(AF_INET,SOCK_DGRAM,0);

    do{
        printf("Enter the message: ");
        scanf("%s",msg);
        sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&server,slen);
        memset(msg1,0x0,512);
        recvfrom(sd,msg1,512,0,(struct sockaddr*)&server,&slen);
        printf("\nReceived message:'%s' from server.\n",msg1);
    }while(strcmp(msg,"stop"));
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
#include<time.h>

#define SERVER_IP "127.0.0.2"
#define SERVER_PORT 6540

void main(){
    time_t ti;
    struct sockaddr_in client,server;
    int sd,slen=sizeof(server),clen=sizeof(client);
    char msg[512];
    char msg1[512] = "Invalid Request";
    char *ptr;

    bzero((char *)&server,slen);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET,SOCK_DGRAM,0);
    bind(sd,(struct sockaddr*)&server,slen);

    while(1){
        do{
            memset(msg,0x0,512);
            recvfrom(sd,msg,512,6,(struct sockaddr*)&client,&clen);
            if(strcmp(msg,"time")==0){
                ti = time(NULL);
                ptr = ctime(&ti);
                sendto(sd,ptr,strlen(ptr)+1,0,(struct sockaddr*)&client,clen);
            }
            else
                sendto(sd,msg1,strlen(msg1)+1,0,(struct sockaddr*)&client,clen);
        }while(strcmp(msg,"stop"));
    }
}