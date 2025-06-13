#pragma once

#include <netinet/in.h>

namespace webmorda
{

class SimpleSocket
{
private:
    struct sockaddr_in _address;
    int _sock;
    int _connection;

public:
    SimpleSocket(int domain, int type, int protocol, int port, unsigned long interface);
    virtual int connectToNetwork(int sock, struct sockaddr_in address) = 0;
    struct sockaddr_in getAddress();
    int getSocket();
    int getConnection();
    void setConnection(int connection);
};

}
