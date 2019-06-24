#include <functional>
#include "Plugin.h"
#include "../ui/utils/ValueFormatters.h"

Plugin::Plugin() {
    //editorWindow = std::make_unique<EditorWindow>();
    editorWindow = new EditorWindow;
}

Plugin::~Plugin() {
    delete editorWindow;
}

//==============================================================================
void Plugin::onCreateParams(ParamManager &manager) {
    Param &paramLeft = manager.addParam(prmGainLeft, "Gain Left", 50);
    Param &paramRight = manager.addParam(prmGainRight, "Gain Right", 50);

    paramLeft.valueFormatter = ValueFormatters::precentageFormatter;
    paramRight.valueFormatter = ValueFormatters::precentageFormatter;

    editorWindow->linkControllers(manager);
    paramManager = &manager;
}

void Plugin::dispatchEvents() {

}

IPluginGUI *Plugin::getGUI() {
    //return dynamic_cast<IPluginGUI*>(editorWindow.get());
    return editorWindow;
}
