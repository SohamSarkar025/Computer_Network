//ASSG10
//Sliding Window Protocol


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
    int sd,w,i,j,count=0;
    char msg[512],buff[512],ack[512];

    bzero((char *)&server,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port = htons(SERVER_PORT);

    bzero((char *)&client,sizeof(client));
    client.sin_family = AF_INET;
    client.sin_addr.s_addr = inet_addr(CLIENT_IP);
    client.sin_port = htons(CLIENT_PORT);

    sd=socket(AF_INET,SOCK_STREAM,0);
    bind(sd,(struct sockaddr*)&client,sizeof(client));
    connect(sd,(struct sockaddr*)&server,sizeof(server));

    do{
        printf("\nEnter a message: ");
        scanf("%s",msg);
        printf("\nEnter window size: ");
        scanf("%d",&w);
        j=0;
        count=0;
        for(i=0;i<strlen(msg);i++){
            if(j<w){
                buff[j]=msg[i];
                j++;
            }
            if(j==w||i==strlen(msg)-1){
                buff[j]='\0';
                send(sd,buff,strlen(buff)+1,0);
                memset(ack,0x0,512);
                recv(sd,ack,512,0);
                printf("%s%d\n",ack,count++);
                j=0;
            }
        }
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
#define SERVER_PORT 6540

void main(){
    struct sockaddr_in client,server;
    int sd, nsd, clen=sizeof(client);
    char msg[512],ack[]="ACKNOWLEDGEMENT RECEIVED";

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
            printf("Data Received: ");
            puts(msg);
            send(nsd,ack,strlen(ack)+1,0);
        }while(strcmp(msg,"stop"));
        close(nsd);
    }
}
