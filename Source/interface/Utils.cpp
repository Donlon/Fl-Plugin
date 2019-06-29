#include <iostream>
#include <mutex>
#include <cstdio>
#include <fp_plugclass.h>

#include "Utils.h"

namespace Utils {
    std::mutex mtx;
}
#ifndef _DEBUG
void Utils::traceDispatchLog(intptr_t ID, intptr_t Index, intptr_t Value) {
}

void Utils::traceProcessParamLog(int index, int value, int recFlags){
}
#else

void Utils::traceDispatchLog(intptr_t id, intptr_t index, intptr_t value) {
    mtx.lock();
    std::cout << "Dispatch from host ";
    const char *name = nullptr;
    bool traceValueAsHex = true;

    switch (id) {
        case FPD_ShowEditor:
            name = "ShowEditor";
            break;
        case FPD_ProcessMode:
            name = "ProcessMode";
            break;
        case FPD_Flush:
            name = "Flush";
            break;
        case FPD_SetBlockSize:
            name = "SetBlockSize";
            traceValueAsHex = false;
            break;
        case FPD_SetSampleRate:
            name = "SetSampleRate";
            traceValueAsHex = false;
            break;
        case FPD_WindowMinMax:
            name = "WindowMinMax";
            break;
        case FPD_KillAVoice:
            name = "KillAVoice";
            break;
        case FPD_UseVoiceLevels:
            name = "UseVoiceLevels";
            break;
        case FPD_SetPreset:
            name = "SetPreset";
            break;
        case FPD_ChanSampleChanged:
            name = "ChanSampleChanged";
            break;
        case FPD_SetEnabled:
            name = "SetEnabled";
            break;
        case FPD_SetPlaying:
            name = "SetPlaying";
            break;
        case FPD_SongPosChanged:
            name = "SongPosChanged";
            break;
        case FPD_SetTimeSig:
            name = "SetTimeSig";
            break;
        case FPD_CollectFile:
            name = "CollectFile";
            break;
        case FPD_SetInternalParam:
            name = "SetInternalParam";
            break;
        case FPD_SetNumSends:
            name = "SetNumSends";
            break;
        case FPD_LoadFile:
            name = "LoadFile";
            break;
        case FPD_SetFitTime:
            name = "SetFitTime";
            break;
        case FPD_SetSamplesPerTick:
            name = "SetSamplesPerTick";
            break;
        case FPD_SetIdleTime:
            name = "SetIdleTime";
            break;
        case FPD_SetFocus:
            name = "SetFocus";
            break;
        case FPD_Transport:
            name = "Transport";
            break;
        case FPD_MIDIIn:
            name = "MIDIIn";
            break;
        case FPD_RoutingChanged:
            name = "RoutingChanged";
            break;
        case FPD_GetParamInfo:
            name = "GetParamInfo";
            break;
        case FPD_ProjLoaded:
            name = "ProjLoaded";
            break;
        case FPD_WrapperLoadState:
            name = "WrapperLoadState";
            break;
        case FPD_ShowSettings:
            name = "ShowSettings";
            break;
        case FPD_SetIOLatency:
            name = "SetIOLatency";
            break;
        case FPD_PreferredNumIO:
            name = "PreferredNumIO";
            break;
        default:
            name = "Unknown";
    }
    std::cout << "id: " << name << "(" << id << "), index: " << index << ", ";

    if (traceValueAsHex) {
        printf("val: 0x%x", (int) value);
    } else {
        printf("val: %d", (int) value);
    }

    std::cout << std::endl;
    mtx.unlock();
}

void Utils::traceProcessParamLog(int index, int value, int recFlags) {
    mtx.lock();
    std::cout << "ProcessParam, index: "
              << index << ", value: " << value << std::endl;
    std::cout << "    RecFlags: ";
    if (recFlags & REC_UpdateValue)
        std::cout << "UpdateValue ";
    if (recFlags & REC_GetValue)
        std::cout << "GetValue ";
    if (recFlags & REC_ShowHint)
        std::cout << "ShowHint ";
    if (recFlags & REC_UpdateControl)
        std::cout << "UpdateControl ";
    if (recFlags & REC_FromMIDI)
        std::cout << "FromMIDI ";
    if (recFlags & REC_NoLink)
        std::cout << "NoLink ";
    if (recFlags & REC_InternalCtrl)
        std::cout << "InternalCtrl ";
    if (recFlags & REC_PlugReserved)
        std::cout << "PlugReserved ";
    std::cout << std::endl;
    mtx.unlock();
}

#endif