#pragma once

#include <string>

struct addrinfo;

namespace Illuminations::Network {
    addrinfo *getAddressInfo(const std::string &hostName, unsigned short port, bool isDatagram);

    void freeAddressInfo(addrinfo *info);
}