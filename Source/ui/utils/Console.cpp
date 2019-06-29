#include <Windows.h>
#include <cstdio>
#include <exception>

#include "Console.h"

namespace Console {
    bool allocated = false;
}

void Console::allocateConsole() {
    if (allocated) {
        throw std::exception("Console has been allocated");
    }
    FILE *_;
    AllocConsole();
    freopen_s(&_, "CONOUT$", "w", stdout);

    ::SetWindowPos(::GetConsoleWindow(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

    allocated = true;
}

void Console::freeConsole() {
    if (!allocated) {
        throw std::exception("Console hasn't been allocated");
    }
    FreeConsole();
    allocated = false;
}
