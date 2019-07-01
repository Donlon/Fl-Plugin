#include <Windows.h>
#include <cstdio>
#include <exception>

#include "Console.h"

namespace Console {
    int allocationCount = 0;
}

void Console::allocateConsole() {
    allocationCount++;

    if (allocationCount > 1) {
        return;
    }

    FILE *_;
    AllocConsole();
    freopen_s(&_, "CONOUT$", "w", stdout);

    ::SetWindowPos(::GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
}

void Console::freeConsole() {
    if (allocationCount <= 0) {
        throw std::exception("Too many calls for freeConsole");
    }

    allocationCount--;

    if (allocationCount > 0) {
        return;
    }
    ::FreeConsole();
}
