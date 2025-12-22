#include <iostream>

#include "../include/libsocket/udp_socket.h"

using namespace libsocket;

class UDPSocket::Impl {
    const SockAddr m_addr;

public:
    void close();
};


UDPSocket::UDPSocket() {

}

UDPSocket::~UDPSocket() {
    m_impl->close();
}

