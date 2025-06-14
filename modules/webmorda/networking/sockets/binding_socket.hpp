#pragma once

#include "simple_socket.hpp"
#include <netinet/in.h>

namespace webmorda
{

class BindingSocket: public SimpleSocket
{
public:
    BindingSocket(int domain, int type, int protocol, int port, unsigned long interface);
    int connectToNetwork(int sock, struct sockaddr_in address);
};

}
