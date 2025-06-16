#include "binding_socket.hpp"
#include "simple_socket.hpp"

#include <netinet/in.h>
#include <sys/socket.h>

using namespace webmorda;

BindingSocket::BindingSocket(int domain, int type, int protocol, int port, unsigned long interface) : SimpleSocket(domain, type, protocol, port, interface)
{
    if (!getSocketState()) {
        _bind_state = false;
        return;
    }

    if (connectToNetwork(getSocket(), getAddress()) < 0) {
        _bind_state = false;
        return;
    }

    _bind_state = true;
}

bool BindingSocket::getBindState(void)
{
    return _bind_state;
}

int BindingSocket::connectToNetwork(int sock, struct sockaddr_in address)
{
    return bind(sock, (struct sockaddr *)&address, sizeof(address));
}
