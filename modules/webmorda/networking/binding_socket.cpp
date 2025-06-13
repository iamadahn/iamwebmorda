#include "binding_socket.hpp"
#include "simple_socket.hpp"

#include <cstdlib>
#include <netinet/in.h>
#include <sys/socket.h>

using namespace webmorda;

BindingSocket::BindingSocket(int domain, int type, int protocol, int port, unsigned long interface) : SimpleSocket(domain, type, protocol, port, interface)
{
    setConnection(connectToNetwork(getSocket(), getAddress()));
    if (getConnection() < 0) {
        exit(EXIT_FAILURE);
    }
}

int BindingSocket::connectToNetwork(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
}
