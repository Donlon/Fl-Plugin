#pragma once

#include "../illuminations/network/StreamConnection.h"
#include "../interface/IPlugin.h"
#include "../interface/Param.h"
#include "../interface/ParamManager.h"
#include "EditorWindow.h"
#include "LightSynthesizer.h"

// the parameter indexes
enum ParamIDs {
    prmBrightness = 1000
};

class Plugin : public IPlugin {
    //std::unique_ptr<EditorWindow> editorWindow;
    EditorWindow *editorWindow = nullptr;
    ParamManager *paramManager = nullptr;
    LightSynthesizer *synth = nullptr;
    Illuminations::Network::StreamConnection *conn = nullptr;
public:
    Plugin();

    ~Plugin() override;

    //==============================================================================
    void onCreateParams(ParamManager &manager) override;

    void dispatchEvents() override;

    IPluginGUI *getGUI() override;

    std::string getHint() override {
        Component *target = editorWindow->getComponentAt(Desktop::getMousePosition());
        if (target) {
            Param *param = paramManager->getParam(target);
            if (param) {
                return param->name;
            }
        }
        return {};
    }
};

