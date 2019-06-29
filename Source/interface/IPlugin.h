#pragma once

class FruityPluginInterface;

class IPluginGUI;

class ParamManager;

class IPlugin {
public:
    FruityPluginInterface *plugin = nullptr;

    virtual ~IPlugin() {};

    virtual void onCreateParams(ParamManager &paramManager) = 0;

    virtual void dispatchEvents() = 0;

    virtual IPluginGUI *getGUI() = 0;

    virtual std::string getHint() = 0;

//    virtual void* getAudioProcessor();
};