IN CLIENT:

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

void main()
{
    struct sockaddr_in server;
    int server_sd;
    char msg_send[512], msg_recv[512];

    bzero((char *)&server, sizeof server);

    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    connect(server_sd, (struct sockaddr *)&server, sizeof server);

    while (1)
    {
        printf("Enter a array to be sorted(eg size elem1 elem2...) or stop to exit: ");
        fgets(msg_send, sizeof msg_send, stdin);
        send(server_sd, msg_send, strlen(msg_send) + 1, 0);

        memset(msg_recv, 0x0, sizeof msg_recv);
        recv(server_sd, msg_recv, sizeof msg_recv, 0);

        printf("Sorted array: %s\n", msg_recv);

        if ((strcmp(msg_send, "stop\n") == 0))
        {
            printf("Stopping client\n");
            break;
        }
    }
    close(server_sd);
}



IN SERVER:


#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5670

void sort(char *str)
{
    int i, j, t, idx, n, arr[50];
    char *tmp = str;

    sscanf(str, "%d %n", &n, &t);
    str += t;

    for (i = 0; i < n; i++)
    {
        sscanf(str, "%d %n", &arr[i], &t);
        str += t;
    }

    for (i = 0; i < n; i++)
    {
        t = arr[i];
        idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (t > arr[j])
            {
                t = arr[j];
                idx = j;
            }
        }
        arr[idx] = arr[i];
        arr[i] = t;
    }

    t = 0;
    for (int i = 0; i < n; i++)
    {
        t += sprintf(&tmp[t], "%d ", arr[i]);
    }
}

void main()
{
    struct sockaddr_in client, server;
    int client_sd, server_sd, clen = sizeof client;
    char msg[512];

    bzero((char *)&server, sizeof server);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(SERVER_IP);

    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    bind(server_sd, (struct sockaddr *)&server, sizeof server);
    listen(server_sd, 5);

    while (1)
    {
        printf("Waiting for client...\n");
        client_sd = accept(server_sd, (struct sockaddr *)&client, &clen);

        printf("Client connected\n");
        while (1)
        {
            memset(msg, 0x0, 512);

            if (recv(client_sd, msg, 512, 0) == 0)
            {
                printf("Client Disconnected\n");
                break;
            }

            sort(msg);
            send(client_sd, msg, strlen(msg) + 1, 0);

            if (strcmp(msg, "stop\n") == 0)
            {
                printf("Client Disconnected\n");
                break;
            }
        }
        close(client_sd);
    }
}