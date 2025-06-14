#pragma once

#include "sockets/listening_socket.hpp"
#include <sys/types.h>
#include <netinet/in.h>

namespace webmorda
{

class SingleClientServer : public ListeningSocket
{
private:
    static const int _buffer_size = 4096;
    int _client_fd;
    struct sockaddr_in _client_address;
    socklen_t _client_address_len;
    unsigned char _buffer[_buffer_size];

public:
    SingleClientServer(int domain, int type, int protocol, int port, unsigned long interface, int backlog);
    void handle();
};

}
