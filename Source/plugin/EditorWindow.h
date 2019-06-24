
#pragma once

#include <JuceHeader.h>
#include "../interface/IPluginGUI.h"
#include "../interface/ParamManager.h"
#include "../PluginInterface.h"

class FruityPluginInterface;

class EditorWindow : public Component,
                     public IPluginGUI {
    std::unique_ptr<Slider> brightnessSlider;

public:
    //==============================================================================
    EditorWindow();

    ~EditorWindow() override;

    //==============================================================================
    void showEditor(void *parent) override;

    void hideEditor() override;

    void *getWindowHandle() override;

    //==============================================================================
    void paint(Graphics &g) override;

    void resized() override;

    //==============================================================================
    void linkControllers(ParamManager &paramManager);

private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorWindow)
};

