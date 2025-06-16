#include "simple_socket.hpp"

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
        _sock_state = false;
    } else {
        _sock_state = true;
    }
}

bool SimpleSocket::getSocketState(void)
{
    return _sock_state;
}

struct sockaddr_in SimpleSocket::getAddress(void)
{
    return _address;
}

int SimpleSocket::getSocket(void)
{
    return _sock;
}
