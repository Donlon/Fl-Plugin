#include <functional>
#include "Plugin.h"
#include "../ui/utils/ValueFormatters.h"

Plugin::Plugin() {
    //editorWindow = std::make_unique<EditorWindow>();
    editorWindow = new EditorWindow;
    synth = new LightSynthesizer(60);
}

Plugin::~Plugin() {
    delete editorWindow;
    delete synth;
}

//==============================================================================
void Plugin::onCreateParams(ParamManager &manager) {
    Param &paramBrightness = manager.addParam(prmBrightness, "Brightness", 10);

    paramBrightness.valueFormatter = ValueFormatters::precentageFormatter;
    paramBrightness.onChangeListener = [this](int val) -> bool {
        this->synth->onParamChange(LightSynthesizer::Brightness, val);
        return false;
    };

    editorWindow->linkControllers(manager);
    paramManager = &manager;
}

void Plugin::dispatchEvents() {

}

IPluginGUI *Plugin::getGUI() {
    //return dynamic_cast<IPluginGUI*>(editorWindow.get());
    return editorWindow;
}
