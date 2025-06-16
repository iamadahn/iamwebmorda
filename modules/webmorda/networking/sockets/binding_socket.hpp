#pragma once

#include "simple_socket.hpp"
#include <netinet/in.h>

namespace webmorda
{

class BindingSocket: public SimpleSocket
{
private:
    bool _bind_state;

protected:
    BindingSocket(int domain, int type, int protocol, int port, unsigned long interface);
    bool getBindState(void);
    int connectToNetwork(int sock, struct sockaddr_in address);
};

}
