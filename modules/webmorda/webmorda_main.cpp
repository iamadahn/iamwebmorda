#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <nuttx/config.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

void serve_file(int client_socket);

extern "C" int main(int argc, FAR char *argv[])
{
    struct addrinfo hints, *res;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int ret = getaddrinfo("google.com", "80", &hints, &res);
    if (ret != 0) {
        printf("Unable to resolve adress, quitting - %d\n", errno);
        return -1;
    }

    usleep(100 * 1000);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        printf("Failed to create a socket - %d.\n", errno);
        close(server_socket);
        return -1;
    }

    struct sockaddr_in server_address = {0}, client_address = {0};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(80);

    ret = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    if (ret < 0) {
        printf("Failed to bind socket to port - %d.\n", errno);
        return -1;
    }

    ret = listen(server_socket, 8);
    if (ret < 0) {
        printf("Failed to start listening for connections - %d.\n", errno);
        close(server_socket);
        return -1;
    }

    while (true) {
        socklen_t len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &len);
        if (client_socket < 0) {
            printf("Failed to accept client - %d.\n", errno);
            continue;
        }

        serve_file(client_socket);

        close(client_socket);
    }

    close(server_socket);
    return 0;
}

void serve_file(int client_socket)
{
    FILE *file = fopen("/mnt/cromfs/index.html", "r");
        if (file == NULL) {
            const char *not_found = "HTTP/1.1 404 Not Found\r\n"
                                    "Content-Type: text/html\r\n"
                                    "Content-Length: 45\r\n"
                                    "\r\n"
                                    "<h1>404 Not Found</h1>";
            send(client_socket, not_found, strlen(not_found), 0);
            return;
        }

        char buffer[1024];
        const char *header = "HTTP/1.1 200 OK\r\n"
                             "Content-Type: text/html\r\n"
                             "Connection: close\r\n"
                             "\r\n";
        send(client_socket, header, strlen(header), 0);

        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            send(client_socket, buffer, strlen(buffer), 0);
        }

        fclose(file);
}
