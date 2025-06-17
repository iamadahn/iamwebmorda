#pragma once

#include "sockets/listening_socket.hpp"
#include <sys/types.h>
#include <netinet/in.h>

namespace webmorda
{

class SingleClientServer : public ListeningSocket
{
private:
    int _client_fd;
    struct sockaddr_in _client_address;
    socklen_t _client_address_len;

    static const int _buffer_size = 4096;
    unsigned char _buffer[_buffer_size];
    bool _state;
    bool _client_connected;

    void acceptClient(void);

public:
    SingleClientServer(int domain, int type, int protocol, int port, unsigned long interface, int backlog);
    bool isClientConnected(void);
    bool getState(void);
    void handle(void);
};

}
