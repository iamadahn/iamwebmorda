#include "simple_socket.hpp"
#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace webmorda;

SimpleSocket::SimpleSocket(int domain, int type, int protocol, int port, unsigned long interface)
{
    // Define adress structure
    _address.sin_family = domain;
    _address.sin_port = htons(port);
    _address.sin_addr.s_addr = htonl(interface);

    // Create socket
    _sock = socket(domain, type, protocol);
    if (_sock < 0) {
        exit(EXIT_FAILURE);
    }
}

struct sockaddr_in SimpleSocket::getAddress()
{
    return _address;
}

int SimpleSocket::getSocket()
{
    return _sock;
}

int SimpleSocket::getConnection()
{
    return _connection;
}

void SimpleSocket::setConnection(int conn)
{
    _connection = conn;
}
