//ASSG Extra-2
//Iterative Chat Server


//Client
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#define CLIENT_IP "127.0.0.1"
#define CLIENT_PORT 4000
#define SERVER_IP "192.168.6.19"
#define SERVER_PORT 5000
int main(){
 struct sockaddr_in client,server;
 int sd;
 char buf[100],str[100];
 bzero(&client,sizeof(client));
 client.sin_family=AF_INET;
 client.sin_port=htons(CLIENT_PORT);
 client.sin_addr.s_addr=inet_addr(CLIENT_IP);
 bzero(&server,sizeof(server));
 server.sin_family=AF_INET;
 server.sin_port=htons(SERVER_PORT);
 server.sin_addr.s_addr=inet_addr(SERVER_IP);
 sd=socket(AF_INET,SOCK_STREAM,0);
 bind(sd,(struct sockaddr*)&client,sizeof(client));
 while(1){
 printf("Enter the message to send to server: ");
 scanf("%s",buf);
 sendto(sd,buf,sizeof(buf),0,(struct sockaddr*)&server,sizeof(server));
 recvfrom(sd,str,sizeof(str),0,NULL,NULL);
 printf("Message from server: %s\n",str);
 if(strcmp(buf,"bye")==0)break;
 }
 close(sd);
 return 0;
}

//Server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#define SERVER_IP "192.168.5.19"
#define SERVER_PORT 8070
int main(){
 struct sockaddr_in server,client;
 int sd,newfd,len=sizeof(client);
 char tmp[512],buf[512];
 bzero(&server,sizeof(server));
 server.sin_family=AF_INET;
 server.sin_port=htons(SERVER_PORT);
 server.sin_addr.s_addr=inet_addr(SERVER_IP);
 sd=socket(AF_INET,SOCK_STREAM,0);
 bind(sd,(struct sockaddr*)&server,sizeof(server));
 listen(sd,3);
 while(1){
 newfd=accept(sd,(struct sockaddr*)&client,&len);
 read(newfd,buf,sizeof(buf));
 printf("From client: %s\n",buf);
 strcpy(tmp,"You have received : ");
 strcat(tmp,buf);
 write(newfd,tmp,strlen(tmp));
 close(newfd);
 }
 close(sd);
 return 0;
}
