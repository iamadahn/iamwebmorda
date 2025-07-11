#pragma once

#include "binding_socket.hpp"

namespace webmorda
{

class ListeningSocket: public BindingSocket
{
private:
    int _backlog;
    int _listening_state;

protected:
    ListeningSocket(int domain, int type, int protocol, int port, unsigned long interface, int backlog);
    bool getListeningState(void);
};

}
