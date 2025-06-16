#include "connecting_socket.hpp"
#include "simple_socket.hpp"

#include <netinet/in.h>
#include <sys/socket.h>

using namespace webmorda;

ConnectingSocket::ConnectingSocket(int domain, int type, int protocol, int port, unsigned long interface) : SimpleSocket(domain, type, protocol, port, interface)
{
    int res = connectToNetwork(getSocket(), getAddress());
    if (res < 0) {
        _connection_state = false;
    }

    _connection_state = true;
}

int ConnectingSocket::connectToNetwork(int sock, struct sockaddr_in address)
{
    return connect(sock, (struct sockaddr *)&address, sizeof(address));
}

bool ConnectingSocket::getConnectionState(void)
{
    return _connection_state;
}
