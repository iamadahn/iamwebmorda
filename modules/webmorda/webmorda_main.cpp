#include <cstdlib>
#include <netinet/in.h>
#include <nuttx/config.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>

#include "networking/single_client_server.hpp"

extern "C" int main(int argc, FAR char *argv[])
{
    struct addrinfo hints, *res;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int ret = getaddrinfo("google.com", "80", &hints, &res);
    if (ret != 0) {
        printf("Unable to resolve adress, quitting\n");
        return EXIT_FAILURE;
    }

    auto server = webmorda::SingleClientServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 1);
    if (!server.getState()) {
        printf("webmorda_main: failed to create SingleClientServer.\n");
        return EXIT_FAILURE;
    }

    while(true) {
        server.handle();
        usleep(100 * 1000);
    }

    return EXIT_SUCCESS;
}

