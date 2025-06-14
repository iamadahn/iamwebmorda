#include "listening_socket.hpp"
#include "binding_socket.hpp"

#include <cstdlib>
#include <sys/socket.h>

using namespace webmorda;

ListeningSocket::ListeningSocket(int domain, int type, int protocol, int port, unsigned long interface, int backlog) : BindingSocket(domain, type, protocol, port, interface)
{
    _backlog = backlog;
    _listening = listen(getSocket(), _backlog);
    if (_listening < 0) {
        exit(EXIT_FAILURE);
    }
}
