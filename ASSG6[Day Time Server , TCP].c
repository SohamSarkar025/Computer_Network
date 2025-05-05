//Day Time Server Using TCP
//ASSG6


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
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6540

void main(){
    struct sockaddr_in client,server;
    int sd;
    char msg[512];

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port=htons(SERVER_PORT);

    bzero((char *)&client, sizeof(client));
    client.sin_family=AF_INET;
    client.sin_addr.s_addr=inet_addr(CLIENT_IP);
    client.sin_port=htons(CLIENT_PORT);

    sd=socket(AF_INET,SOCK_STREAM,0);
    connect(sd,(struct sockaddr *)&server,sizeof(server));

    do{
        printf("Enter a message: ");
        scanf("%s",msg);
        send(sd,msg,strlen(msg)+1,0);
        memset(msg,0x0,512);
        recv(sd,msg,512,0);
        printf("\nReceived message: '%s' from server.\n",msg);

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

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6540

void main(){
    time_t ti;

    struct sockaddr_in client,server;
    int sd, nsd, clen=sizeof(client);
    char msg[512];
    char msg1[] = "Invalid Request";
    char *ptr;

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port=htons(SERVER_PORT);
    
    sd=socket(AF_INET,SOCK_STREAM,0);
    bind(sd,(struct sockaddr*)&server,sizeof(server));
    listen(sd, 5);

    while(1){
    nsd=accept(sd,(struct sockaddr*)&client,&clen);
    do{
        memset(msg,0x0,512);
        recv(nsd,msg,512,0);
        if(strcmp(msg,"time")==0){
            ti = time(NULL);
            ptr = ctime(&ti);
            send(nsd,ptr,strlen(ptr)+1,0);
        }
        else
            send(nsd,msg1,strlen(msg1)+1,0);
    }while(strcmp(msg,"stop"));
    close(nsd);
    }
}
