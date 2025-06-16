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
