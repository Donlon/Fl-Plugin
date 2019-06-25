#include <ws2def.h>
#include <string>

namespace Illuminations::Network {
    static addrinfo *getAddressInfo(const std::string &hostName, unsigned short port, bool isDatagram);

    static void freeAddressInfo(addrinfo *info);
}