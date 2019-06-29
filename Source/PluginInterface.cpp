#include <fp_plugclass.h>
#include <cassert>

#include "PluginInterface.h"
#include "plugin/Plugin.h"
#include "interface/Param.h"

#if defined __WIN64 || 1
extern "C" __declspec(dllexport)  TFruityPlug *_stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag)
#else
//extern "C" TFruityPlug * _stdcall CreatePlugInstance(TFruityPlugHost *Host, int Tag)
#endif
{
    juce::initialiseJuce_GUI();
    Process::setCurrentModuleInstanceHandle(HInstance);

    return new FruityPluginInterface(Tag, Host);
};

// the information structure describing this plugin to the host
TFruityPlugInfo PlugInfo = {
        CurrentSDKVersion,
        "Fl Plugin",
        "Fl Plugin Test",
        FPF_Type_Effect,
        0/*NumParams*/,
        0  // infinite
};

FruityPluginInterface::FruityPluginInterface(int Tag, TFruityPlugHost *Host)
        : TCPPFruityPlug(Tag, Host, nullptr), paramManager(dynamic_cast<TCPPFruityPlug *>(this)) {
    createPlugin();
    //ResetParams();
    Info = &PlugInfo;
    PlugInfo.NumParams = (int) paramManager.getParamList().size();
}

void FruityPluginInterface::createPlugin() {
    plugin = new Plugin;
    plugin->plugin = this;
    plugin->onCreateParams(paramManager);
    pluginGui = plugin->getGUI();
}

void __stdcall FruityPluginInterface::DestroyObject() {
    delete plugin;
}

intptr_t __stdcall FruityPluginInterface::Dispatcher(intptr_t ID, intptr_t Index, intptr_t Value) {
    switch (ID) {
        // show the editor
        case FPD_ShowEditor : {
            if (!pluginGui) {
                break;
            }
            if (Value == 0) {
                pluginGui->hideEditor();
            } else {
                pluginGui->showEditor((void *) Value);
            }

            EditorHandle = (HWND) pluginGui->getWindowHandle();
            break;
        }
        default:
            break;
    }

    return 0;
}

void __stdcall FruityPluginInterface::Eff_Render(PWAV32FS SourceBuffer, PWAV32FS DestBuffer, int Length) {
    Param &param = paramManager.getParamByPosition(0);

    auto gain = static_cast<float>(param.value) / 100.f;


    for (int i = 0; i < Length; i++) {
        (*DestBuffer)[i][0] = (*SourceBuffer)[i][0] * gain;
        (*DestBuffer)[i][1] = (*SourceBuffer)[i][1] * gain;
    }
}

void __stdcall FruityPluginInterface::GetName(int Section, int Index, int Value, char *Name) {
    if (Section == FPN_Param) {
        Param &param = paramManager.getParamByPosition(Index);
        strncpy(Name, param.name.c_str(), 256);
    } else if (Section == FPN_ParamValue) {
        Param &param = paramManager.getParamByPosition(Index);
        std::string &str = param.desc;
        strncpy(Name, str.c_str(), 256);
    }
}

void FruityPluginInterface::Idle() {
    std::string hint = plugin->getHint();
    strncpy(AppHint, hint.c_str(), 256);
    PlugHost->OnHint(HostTag, AppHint);
}

int __stdcall FruityPluginInterface::ProcessParam(int index, int value, int recFlags) {
    if (recFlags & REC_GetValue) {
        return paramManager.getValue(index);
    }

    // translate from 0..65536 to the parameter's range
    if (recFlags & REC_FromMIDI) {
        value = value * 100 / 65536;
    }

    if (recFlags & REC_UpdateValue) {
        paramManager.setValue(index, value, false);

        // if the parameter value has changed,
        // then we notify the host that the controller has changed
        // (!) beware of messages that are sent by (other ?) internal controllers
        // (!) convert the value from its own range to 0..65536
        ///if ((recFlags & REC_InternalCtrl) == 0) {
        ///    DebugBreak();
        ///    PlugHost->OnControllerChanged(HostTag, index, value);
        ///}
    }

    // update the parameter control's value
    if (recFlags & REC_UpdateControl) {
        paramManager.setValue(index, value, false);
    }

    // we show the parameter value as a hint
    if (recFlags & REC_ShowHint) {
        char t[32];
        sprintf(t, "%d%%", value);
        PlugHost->OnHint(HostTag, t);
    }

    // make sure we return the value
    return value;
}

void FruityPluginInterface::ResetParams() {
    for (Param *param : paramManager.getParamList()) {
        assert(param != nullptr);
        param->paramSetter(param->defaultValue);
    }
}

void __stdcall FruityPluginInterface::SaveRestoreState(IStream *Stream, BOOL Save) {
    if (Save) {
        paramManager.saveToStream(Stream);
    } else {
        paramManager.loadFromStream(Stream);
    }
}
