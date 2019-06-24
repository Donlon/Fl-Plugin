#include <ws2def.h>
#include <WS2tcpip.h>

#include "Utils.h"

addrinfo *Illuminations::Network::getAddressInfo(const std::string &hostName, bool isDatagram) {
    struct addrinfo hints{};

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = isDatagram ? SOCK_DGRAM : SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;

    struct addrinfo *info = nullptr;

    if (getaddrinfo(hostName.data(), nullptr, &hints, &info) == 0) {
        return info;
    } else {
        return nullptr;
    }
}

void Illuminations::Network::freeAddressInfo(addrinfo *info) {
    freeaddrinfo(info);
}
