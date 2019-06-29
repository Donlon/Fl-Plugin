#pragma once

#include <cstdint>

namespace Utils {
    void traceDispatchLog(intptr_t id, intptr_t index, intptr_t value);

    void traceProcessParamLog(int index, int value, int recFlags);
}
