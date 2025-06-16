#pragma once

#include "simple_socket.hpp"
#include <netinet/in.h>

namespace webmorda
{

class ConnectingSocket: public SimpleSocket
{
    bool _connection_state;
    int connectToNetwork(int sock, struct sockaddr_in address);

public:
    ConnectingSocket(int domain, int type, int protocol, int port, unsigned long interface);
    bool getConnectionState(void);
};

}
