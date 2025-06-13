#pragma once

#include "simple_socket.hpp"
#include <netinet/in.h>

namespace webmorda
{

class ConnectingSocket: public SimpleSocket
{
public:
    ConnectingSocket(int domain, int type, int protocol, int port, unsigned long interface);
    int connectToNetwork(int sock, struct sockaddr_in address);
};

}
