#pragma once

#include <netinet/in.h>

namespace webmorda
{

class SimpleSocket
{
private:
    struct sockaddr_in _address;
    int _sock;
    bool _sock_state;

protected:
    SimpleSocket(int domain, int type, int protocol, int port, unsigned long interface);
    int getSocket(void);
    bool getSocketState(void);
    struct sockaddr_in getAddress(void);
    virtual int connectToNetwork(int sock, struct sockaddr_in address) = 0;
};

}
