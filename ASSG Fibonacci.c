IN SERVER:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 8080

void generate_fibonacci(int *fib, int n) {
    if (n > 0) fib[0] = 0;
    if (n > 1) fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    printf("Server is listening on port %d...\n", PORT);
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    
    int n;
    read(new_socket, &n, sizeof(n));

    int fib[100];  // adjust size as needed
    generate_fibonacci(fib, n);

    write(new_socket, fib, n * sizeof(int));
    
    printf("Sent %d Fibonacci numbers to client.\n", n);

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
    
    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    
    int n;
    printf("Enter number of Fibonacci terms: ");
    scanf("%d", &n);

    write(sock, &n, sizeof(n));

    int fib[100]; // size should match server's limit
    read(sock, fib, n * sizeof(int));

    printf("Fibonacci Series:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", fib[i]);
    printf("\n");

    close(sock);
    return 0;
}

