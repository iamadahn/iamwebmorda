#include "single_client_server.hpp"
#include "sockets/listening_socket.hpp"

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

using namespace webmorda;

SingleClientServer::SingleClientServer(int domain, int type, int protocol, int port, unsigned long interface, int backlog) : ListeningSocket(domain, type, protocol, port, interface, backlog)
{
    if (!getListeningState()) {
        _state = false;
        return;
    }

    _client_connected = false;
    _state = true;
}

bool SingleClientServer::getState(void)
{
    return _state;
}

void SingleClientServer::handle(void)
{
    if (!_client_connected) {
        acceptClient();
    }

    int ret = read(_client_fd, _buffer, _buffer_size);

    printf("%s", _buffer);
    bzero(_buffer, _buffer_size);
    char response[] = "HTTP/1.1 200 OK\r\n"
                  "Content-Type: text/html\r\n"
                  "Content-Length: 13\r\n"
                  "\r\n"
                  "Hello, NuttX!";

    write(_client_fd, response, strlen(response));
}

void SingleClientServer::acceptClient(void)
{
    _client_fd = accept(getSocket(), (struct sockaddr *)&_client_address, &_client_address_len);
    if (_client_fd < 0) {
        _client_connected = false;
    } else {
        _client_connected = true;
    }
}
