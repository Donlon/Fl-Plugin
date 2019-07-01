#include "PluginInterfaceSEHWrapper.h"

PluginInterfaceSEHWrapper::PluginInterfaceSEHWrapper(int Tag, TFruityPlugHost *Host)
        : plugin(new FruityPluginInterface(Tag, Host)) {
}

PluginInterfaceSEHWrapper::~PluginInterfaceSEHWrapper() {
    delete plugin;
}

int PluginInterfaceSEHWrapper::handleSEH(const char *func, EXCEPTION_POINTERS *ep) {
    if (!ep) {
        MessageBoxA(NULL, "Exception pointer is null", func, MB_OK);
        return EXCEPTION_EXECUTE_HANDLER;
    }
    DebugBreak();

    EXCEPTION_RECORD &record = *ep->ExceptionRecord;
    char buffer[1024];
    sprintf_s(buffer, 1024,
              "Code: 0x%x, flags: 0x%x, address:0x%p",
              record.ExceptionCode,
              record.ExceptionFlags,
              record.ExceptionAddress);

    std::string msg = std::string("Error in ") + func;
    MessageBoxA(NULL, buffer, "Error", MB_OK);

    return EXCEPTION_EXECUTE_HANDLER;
}

void PluginInterfaceSEHWrapper::DestroyObject() {
    __try
    {
        plugin->DestroyObject();
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

intptr_t PluginInterfaceSEHWrapper::Dispatcher(intptr_t ID, intptr_t Index, intptr_t Value) {
    intptr_t res = 0;
    __try
    {
        res = plugin->Dispatcher(ID, Index, Value);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
    return res;
}

void PluginInterfaceSEHWrapper::Idle_Public() {
    __try
    {
        plugin->Idle_Public();
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

void PluginInterfaceSEHWrapper::SaveRestoreState(IStream *Stream, BOOL Save) {
    __try
    {
        plugin->SaveRestoreState(Stream, Save);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

void PluginInterfaceSEHWrapper::GetName(int Section, int Index, int Value, char *Name) {
    __try
    {
        plugin->GetName(Section, Index, Value, Name);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

int PluginInterfaceSEHWrapper::ProcessEvent(int EventID, int EventValue, int Flags) {
    int res = 0;
    __try
    {
        res = plugin->ProcessEvent(EventID, EventValue, Flags);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
    return res;
}

int PluginInterfaceSEHWrapper::ProcessParam(int Index, int Value, int RECFlags) {
    int res = 0;
    __try
    {
        res = plugin->ProcessParam(Index, Value, RECFlags);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
    return res;
}

void PluginInterfaceSEHWrapper::Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length) {
    __try
    {
        plugin->Eff_Render(SourceBuffer, DestBuffer, Length);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

void PluginInterfaceSEHWrapper::Gen_Render(PWAV32FS DestBuffer, int &Length) {
    __try
    {
        plugin->Gen_Render(DestBuffer, Length);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

TVoiceHandle PluginInterfaceSEHWrapper::TriggerVoice(PVoiceParams VoiceParams, intptr_t SetTag) {
    TVoiceHandle res = 0;
    __try
    {
        res = plugin->TriggerVoice(VoiceParams, SetTag);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
    return res;
}

void PluginInterfaceSEHWrapper::Voice_Release(TVoiceHandle Handle) {
    __try
    {
        plugin->Voice_Release(Handle);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

void PluginInterfaceSEHWrapper::Voice_Kill(TVoiceHandle Handle) {
    __try
    {
        plugin->Voice_Kill(Handle);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

int PluginInterfaceSEHWrapper::Voice_ProcessEvent(TVoiceHandle Handle, int EventID, int EventValue, int Flags) {
    int res = 0;
    __try
    {
        res = plugin->Voice_ProcessEvent(Handle, EventID, EventValue, Flags);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
    return res;
}

int PluginInterfaceSEHWrapper::Voice_Render(TVoiceHandle Handle, PWAV32FS DestBuffer, int &Length) {
    int res = 0;
    __try
    {
        res = plugin->Voice_Render(Handle, DestBuffer, Length);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
    return res;
}

void PluginInterfaceSEHWrapper::NewTick() {
    __try
    {
        plugin->NewTick();
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

void PluginInterfaceSEHWrapper::MIDITick() {
    __try
    {
        plugin->MIDITick();
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

void PluginInterfaceSEHWrapper::MIDIIn(int &Msg) {
    __try
    {
        plugin->MIDIIn(Msg);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

void PluginInterfaceSEHWrapper::MsgIn(intptr_t Msg) {
    __try
    {
        plugin->MsgIn(Msg);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}

int PluginInterfaceSEHWrapper::OutputVoice_ProcessEvent(TOutVoiceHandle Handle, int EventID, int EventValue,
                                                        int Flags) {
    int res = 0;
    __try
    {
        res = plugin->OutputVoice_ProcessEvent(Handle, EventID, EventValue, Flags);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
    return res;
}

void PluginInterfaceSEHWrapper::OutputVoice_Kill(TVoiceHandle Handle) {
    __try
    {
        plugin->OutputVoice_Kill(Handle);
    }
    __except(handleSEH(__FUNCTION__, GetExceptionInformation()))
    {
        printf("New Exception in %s", __FUNCTION__);
    }
}
