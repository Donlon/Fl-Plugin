#include <Windows.h>
#include <cstdio>

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    printf("hModule: %p, lpReserved: %p\n", hModule, lpReserved);

    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            OutputDebugString("Process attach.");
            break;

        case DLL_PROCESS_DETACH:
            OutputDebugString("Process detach.");
            break;

        case DLL_THREAD_ATTACH:
            OutputDebugString("Thread attach.");
            break;

        case DLL_THREAD_DETACH:
            OutputDebugString("Thread detach.");
            break;
    }

    return TRUE;
}
