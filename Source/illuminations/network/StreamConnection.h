#pragma once

#include <JuceHeader.h>
#include <WinSock2.h>

#include "Utils.h"

struct addrinfo;

namespace Illuminations::Network {
    struct Session {
        char s[16];
    };

    template<typename Type>
    class Buffer : public std::basic_string<Type> {
    };

    class StreamConnection {
        addrinfo *addressInfo = nullptr;
        SOCKET sock = INVALID_SOCKET;
        Buffer<unsigned char> sendBuffer;
        int seq = 0;

    public:
        StreamConnection(std::string &addr, int port);

        ~StreamConnection();

        template<typename T>
        void update(Buffer<T> buffer) {
            send(buffer.data(), buffer.length() * sizeof(T), 0, (int) buffer.length());
        }

        template<typename T>
        void update(std::basic_string<T> buffer) {
            send(buffer.data(), buffer.length() * sizeof(T), 0, (int) buffer.length());
        }

        void send(const void *buffer, size_t len, int rangeStart, int rangeEnd);

    };
}

