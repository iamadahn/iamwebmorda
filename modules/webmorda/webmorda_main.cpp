#include <cstdlib>
#include <netinet/in.h>
#include <nuttx/config.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include "networking/listening_socket.hpp"

extern "C" int main(int argc, FAR char *argv[])
{
    printf("webmorda\n");

    struct addrinfo hints, *res;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int ret = getaddrinfo("google.com", "80", &hints, &res);
    printf("getaddrinfo status: %d\n", ret);
    if (ret != 0) {
        printf("Unable to resolve adress, quitting\n");
        return EXIT_FAILURE;
    }

    auto sock = webmorda::ListeningSocket(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 1);
    printf("Socket fd - %d, connection statis - %d", sock.getSocket(), sock.getConnection());

    return EXIT_SUCCESS;
}

