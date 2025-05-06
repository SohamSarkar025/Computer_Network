//ASSG Extra-2
//Iterative Chat Server


//Client
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define SERVER_PORT 5550
#define SERVER_IP "127.0.0.1"

int main(){
    struct sockaddr_in server;
    char msg[512], msg1[512];
    int sd, slen = sizeof(server);

    // Setup server address
    bzero((char*)&server, slen);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);

    // No bind() needed for client
    connect(sd, (struct sockaddr*)&server, slen);
    memset(msg1, 0x0, 512);
    recv(sd, msg1, 512, 0);
    printf("\n%s\n", msg1);

    do {
        printf("\nEnter a message to the server: ");
        fgets(msg, sizeof(msg), stdin);
        msg[strcspn(msg, "\n")] = 0;

        send(sd, msg, strlen(msg)+1, 0);

        memset(msg1, 0x0, 512);
        recv(sd, msg1, 512, 0);
        printf("Message Received from Server: %s\n", msg1);
    } while (strcmp(msg, "stop"));

    close(sd);
    return 0;
}

//Server
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define SERVER_PORT 5550
#define SERVER_IP "127.0.0.1"

int main(){
    struct sockaddr_in client, server;
    char msg[512], reply[512];
    int sd, nsd;
    socklen_t clen = sizeof(client);

    // Set up server structure
    bzero((char*)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Create socket
    sd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind to the server address
    bind(sd, (struct sockaddr*)&server, sizeof(server));
       
    // Listen for connections
    listen(sd, 5);
    printf("Server is running and waiting for connections...\n");

    while(1){
        nsd = accept(sd, (struct sockaddr*)&client, &clen);

        strcpy(reply, "Welcome to Chat Server!!");
        send(nsd, reply, strlen(reply) + 1, 0);

        do {
            memset(msg, 0x0, 512);
            recv(nsd, msg, 512, 0);
            printf("Message Received: %s\n", msg);

            printf("Enter Reply: ");
            fgets(reply, sizeof(reply), stdin);
            reply[strcspn(reply, "\n")] = 0;

            send(nsd, reply, strlen(reply) + 1, 0);
        } while (strcmp(msg, "stop") != 0);

        close(nsd);
        printf("Client disconnected.\n");
    }

    close(sd);
    return 0;
}
