
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

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6540

void main(){
     struct sockaddr_in client,server;
    int sd, nsd, clen=sizeof(client);
    char msg[512];

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port=htons(SERVER_PORT);
    
    sd=socket(AF_INET,SOCK_DGRAM,0);
    bind(sd,(struct sockaddr*)&server,sizeof(server));
    // listen(sd, 5);

    while(1){
    do{
        memset(msg,0x0,512);
        recvfrom(sd,msg,512,0,(struct sockaddr*)&client,&clen);
        sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&client,sizeof(client));
    }while(strcmp(msg,"stop"));
    }
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
    int sd,slen=sizeof(server),clen=sizeof(client);
    char msg[512];
    char msg1[512] = "Invalid Request";
    char *ptr;

    bzero((char *)&server,sizeof(server));
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
                // printf("ok");
                ti = time(NULL);
                ptr = ctime(&ti);
                sendto(sd,ptr,strlen(ptr)+1,0,(struct sockaddr*)&client,clen);
            }
            else
                sendto(sd,msg1,strlen(msg1)+1,0,(struct sockaddr*)&client,clen);
        }while(strcmp(msg,"stop"));
    }
}
