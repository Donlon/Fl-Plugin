#include <WinSock2.h>
#include <WS2tcpip.h>

#include "Utils.h"

#ifdef _WINDOWS
#pragma comment(lib, "Ws2_32.lib")
#endif

int Illuminations::Network::initNetwork() {
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(2, 2);
    int err = WSAStartup(wVersionRequested, &wsaData);
    return err;
}

addrinfo *Illuminations::Network::getAddressInfo(const std::string &hostName, unsigned short port, bool isDatagram) {
    struct addrinfo hints{};

    hints.ai_family = AF_UNSPEC;
    hints.ai_protocol = IPPROTO_IP;
    hints.ai_socktype = isDatagram ? SOCK_DGRAM : SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    struct addrinfo *info = nullptr;

    if (getaddrinfo(hostName.data(), std::to_string(port).data(), &hints, &info) == 0) {
        return info;
    } else {
        return nullptr;
    }
}

void Illuminations::Network::freeAddressInfo(addrinfo *info) {
    freeaddrinfo(info);
}
