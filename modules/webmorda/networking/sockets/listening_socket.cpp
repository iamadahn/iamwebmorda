#include "listening_socket.hpp"
#include "binding_socket.hpp"

#include <sys/socket.h>

using namespace webmorda;

ListeningSocket::ListeningSocket(int domain, int type, int protocol, int port, unsigned long interface, int backlog) : BindingSocket(domain, type, protocol, port, interface)
{
    _backlog = backlog;
    int res = listen(getSocket(), _backlog);
    if (res < 0) {
        _listening_state = false;
        return;
    }

    _listening_state = true;
}

bool ListeningSocket::getListeningState(void)
{
    return _listening_state;
}
