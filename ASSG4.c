
//Write a program client will accept a message from user and send it to the server

// Client 

#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 4500
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4501

int main(){
    struct sockaddr_in client,server;
    int sd;
    char msg[512];
    
    bzero((char*)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    bzero((char*)&client,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client.sin_port = htons(CLIENT_PORT);

    sd = socket(AF_INET,SOCK_STREAM,0);
    connect(sd,(struct sockaddr*)&server,sizeof(server));
    do{
        printf("Enter a message: ");
        scanf("%s",msg);
        send(sd,msg,strlen(msg)+1,0);
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

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 4501
int main(){
    struct sockaddr_in client,server;
    int sd,nsd,clen=sizeof(client);
    char msg[512];

    bzero((char*)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    sd = socket(AF_INET,SOCK_STREAM,0);
    bind(sd,(struct sockaddr*)&server,sizeof(server));
    listen(sd,5);
    while(1){
        nsd = accept(sd,(struct sockaddr*)&client,&clen);
        do{
            memset(msg,0x0,512);
            recv(nsd,msg,512,0);
            printf("Received message:%s client's IP: %s client's port:%u\n",msg,inet_ntoa(client.sin_addr),htons(client.sin_port));
        }
        while(strcmp(msg,"stop"));
        close(nsd);
    }
}

