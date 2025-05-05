IN SERVER:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

int search(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key)
            return i; // return index if found
    }
    return -1; // not found
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);
    
    printf("Server is waiting for client...\n");
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    
    int n, key, arr[100];
    read(new_socket, &n, sizeof(n));
    read(new_socket, arr, n * sizeof(int));
    read(new_socket, &key, sizeof(key));

    int result = search(arr, n, key);
    write(new_socket, &result, sizeof(result));
    
    printf("Search result sent to client.\n");

    close(new_socket);
    close(server_fd);
    return 0;
}




IN CLIENT:


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    
    int n, key, arr[100];
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter key to search: ");
    scanf("%d", &key);

    write(sock, &n, sizeof(n));
    write(sock, arr, n * sizeof(int));
    write(sock, &key, sizeof(key));
    
    int result;
    read(sock, &result, sizeof(result));
    
    if (result == -1)
        printf("Element not found.\n");
    else
        printf("Element found at index: %d\n", result+1);
    
    close(sock);
    return 0;
}

