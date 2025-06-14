#include "server.hpp"
#include "sockets/listening_socket.hpp"
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstdlib>
#include <stdio.h>

using namespace webmorda;

Server::Server(int domain, int type, int protocol, int port, unsigned long interface, int backlog) : ListeningSocket(domain, type, protocol, port, interface, backlog)
{
    _server_sock = accept(getSocket(), (struct sockaddr *)&_client_address, &_client_address_len);
    if (_server_sock < 0) {
        exit(EXIT_FAILURE);
    }
}

void Server::handle()
{
    read(_server_sock, _buffer, _buffer_size);
    printf("%s", _buffer);
    bzero(_buffer, _buffer_size);
    char response[] = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html\r\n"
                  "Content-Length: 13\r\n"
                  "\r\n"
                  "Hello, NuttX!";

    write(_server_sock, response, strlen(response));
}
