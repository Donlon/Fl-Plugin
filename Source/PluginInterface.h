#pragma once

#include <JuceHeader.h>
#include <fp_cplug.h>

#include "plugin/EditorWindow.h"
#include "interface/ParamManager.h"
#include "interface/IPlugin.h"
#include "interface/IPluginGUI.h"

extern "C" __declspec(dllexport)  TFruityPlug *_stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag);

class FruityPluginInterface : public TCPPFruityPlug {
    IPlugin *plugin = nullptr;

    IPluginGUI *pluginGui = nullptr;

    ParamManager paramManager;

public:
    FruityPluginInterface(int Tag, TFruityPlugHost *Host);

private:
    void createPlugin();

    void _stdcall DestroyObject() override;

    intptr_t _stdcall Dispatcher(intptr_t ID, intptr_t Index, intptr_t Value) override;

    void Idle() override;

    void _stdcall SaveRestoreState(IStream *Stream, BOOL Save) override;

    // names (see FPN_Param) (Name must be at least 256 chars long)
    void _stdcall GetName(int Section, int Index, int Value, char *Name) override;

    // events
    int _stdcall ProcessParam(int Index, int Value, int RECFlags) override;

    // effect processing (source & dest can be the same)
    void _stdcall Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length) override;

    void ResetParams();
};