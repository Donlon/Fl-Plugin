#pragma once

#include "PluginInterface.h"

class PluginInterfaceSEHWrapper : public TFruityPlug {
    TFruityPlug *plugin;

    int handleSEH(const char *func, struct _EXCEPTION_POINTERS *ep);

public:
    PluginInterfaceSEHWrapper(int Tag, TFruityPlugHost *Host);

    ~PluginInterfaceSEHWrapper() override;

    void _stdcall DestroyObject() override;

    intptr_t _stdcall Dispatcher(intptr_t ID, intptr_t Index, intptr_t Value) override;

    void _stdcall Idle_Public() override;

    void _stdcall SaveRestoreState(IStream *Stream, BOOL Save) override;

    // names (see FPN_Param) (Name must be at least 256 chars long)
    void _stdcall GetName(int Section, int Index, int Value, char *Name) override;

    // events
    int _stdcall ProcessEvent(int EventID, int EventValue, int Flags) override;

    int _stdcall ProcessParam(int Index, int Value, int RECFlags) override;

    // effect processing (source & dest can be the same)
    void _stdcall Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length) override;

    // generator processing (can render less than length)
    void _stdcall Gen_Render(PWAV32FS DestBuffer, int &Length) override;

    // voice handling
    TVoiceHandle _stdcall TriggerVoice(PVoiceParams VoiceParams, intptr_t SetTag) override;

    void _stdcall Voice_Release(TVoiceHandle Handle) override;

    void _stdcall Voice_Kill(TVoiceHandle Handle) override;

    int _stdcall Voice_ProcessEvent(TVoiceHandle Handle, int EventID, int EventValue, int Flags) override;

    int _stdcall Voice_Render(TVoiceHandle Handle, PWAV32FS DestBuffer, int &Length) override;

    // (see FPF_WantNewTick) called before a new tick is mixed (not played)
    // internal controller plugins should call OnControllerChanged from here
    void _stdcall NewTick() override;

    // (see FHD_WantMIDITick) called when a tick is being played (not mixed) (not used yet)
    void _stdcall MIDITick() override;

    // MIDI input message (see FHD_WantMIDIInput & TMIDIOutMsg) (set Msg to MIDIMsg_Null if it has to be killed)
    void _stdcall MIDIIn(int &Msg) override;

    // buffered messages to itself (see PlugMsg_Delayed)
    void _stdcall MsgIn(intptr_t Msg) override;

    // voice handling
    int _stdcall OutputVoice_ProcessEvent(TOutVoiceHandle Handle, int EventID, int EventValue, int Flags) override;

    void _stdcall OutputVoice_Kill(TVoiceHandle Handle) override;
};

