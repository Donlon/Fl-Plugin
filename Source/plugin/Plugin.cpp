#include <functional>

#include "../illuminations/network/StreamConnection.h"
#include "../interface/Param.h"
#include "../interface/ParamManager.h"
#include "../ui/utils/Console.h"
#include "../ui/utils/ValueFormatters.h"
#include "EditorWindow.h"
#include "LightSynthesizer.h"
#include "Plugin.h"

using namespace Illuminations::Network;

#define CONSOLE_DEBUGGING

Plugin::Plugin() {
#ifdef CONSOLE_DEBUGGING
    Console::allocateConsole();
#endif
    //editorWindow = std::make_unique<EditorWindow>();
    editorWindow = new EditorWindow;
    synth = new LightSynthesizer(60);

    Illuminations::Network::initNetwork();

    std::string s = ("rpi");
    conn = new StreamConnection(s, 1055);

    synth->onCanvasUpdate = [this](LightSynthesizer &obj) {
        std::basic_string<rgb888_t> &buf = obj.getBuffer();
        this->conn->update(buf);
    };

    std::cout << "Plugin created." << std::endl;
}

Plugin::~Plugin() {
    delete editorWindow;
    delete synth;

#ifdef CONSOLE_DEBUGGING
    Console::freeConsole();
#endif
}

//==============================================================================
void Plugin::onCreateParams(ParamManager &manager) {
    Param &paramBrightness = manager.addParam(prmBrightness, "Brightness", 10);

    paramBrightness.valueFormatter = ValueFormatters::precentageFormatter;
    paramBrightness.onChangeListener = [this](int val) -> bool {
        this->synth->onParamChange(LightSynthesizer::Brightness, val);
        this->synth->triggerUpdate();
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

std::string Plugin::getHint() {
    Component *target = editorWindow->getComponentAt(Desktop::getMousePosition());
    if (target) {
        Param *param = paramManager->getParam(target);
        if (param) {
            return param->name;
        }
    }
    return {};
}
