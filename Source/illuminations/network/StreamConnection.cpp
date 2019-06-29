#include <WinSock2.h>
#include <ws2ipdef.h>

#include "StreamConnection.h"

using namespace Illuminations::Network;

StreamConnection::StreamConnection(std::string &addr, unsigned short port) {
    setServerAddress(addr, port);
}

StreamConnection::~StreamConnection() {
    Illuminations::Network::freeAddressInfo(addressInfo);
}

void StreamConnection::setServerAddress(std::string &addr, unsigned short port) {
    addressInfo = Illuminations::Network::getAddressInfo(addr, port, true);
    connect();
}

void StreamConnection::connect() {
    if (!addressInfo) {
        return; // TODO: feedback to frontend
    }

    sock = socket(addressInfo->ai_addr->sa_family, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        throw std::exception("Invalid socket");
    }
    switch (addressInfo->ai_addr->sa_family) {
        case AF_INET:
            ::connect(sock, addressInfo->ai_addr, sizeof(struct sockaddr_in));
            break;
        case AF_INET6:
            ::connect(sock, addressInfo->ai_addr, sizeof(struct sockaddr_in6));
            break;
        default:
            throw std::exception("Unexpected SA family");
    }
}

void StreamConnection::send(const void *buffer, size_t len, int rangeStart, int rangeEnd) {
    sendBuffer.clear();
    sendBuffer.append((const unsigned char *) &seq, sizeof(int32_t));
    uint16_t contentLen = len + sizeof(uint16_t) + sizeof(uint8_t) + 2 * sizeof(uint16_t);
    sendBuffer.append((const unsigned char *) &contentLen, sizeof(uint16_t));

    uint16_t id = 0;
    sendBuffer.append((const unsigned char *) &id, sizeof(uint16_t));
    uint8_t type = 0x01;
    sendBuffer.append((const unsigned char *) &type, sizeof(uint8_t));
    sendBuffer.append((const unsigned char *) &rangeStart, sizeof(uint16_t));
    uint16_t size = rangeStart - rangeEnd;
    sendBuffer.append((const unsigned char *) &size, sizeof(uint16_t));

    sendBuffer.append((const unsigned char *) buffer, len);
    ::send(sock, (const char *) sendBuffer.data(), sendBuffer.length(), 0);
}
