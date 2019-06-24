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
    Param &paramBrightness = manager.addParam(prmBrightness, "Brightness", 10);

    paramBrightness.valueFormatter = ValueFormatters::precentageFormatter;

    editorWindow->linkControllers(manager);
    paramManager = &manager;
}

void Plugin::dispatchEvents() {

}

IPluginGUI *Plugin::getGUI() {
    //return dynamic_cast<IPluginGUI*>(editorWindow.get());
    return editorWindow;
}
