#pragma once

#include "../interface/IPlugin.h"

class ParamManager;

// the parameter indexes
enum ParamIDs {
    prmBrightness = 1000
};

class LightSynthesizer;

class EditorWindow;

namespace Illuminations::Network {
    class StreamConnection;
}

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

    std::string getHint() override;
};

