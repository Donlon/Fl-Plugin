#include <fp_cplug.h>
#include "EditorWindow.h"
#include "Plugin.h"
#include "../PluginInterface.h"
#include "../ui/SliderEx.h"

//==============================================================================
EditorWindow::EditorWindow() {
    leftSlider = std::make_unique<SliderEx>(Slider::LinearVertical, Slider::NoTextBox);
    rightSlider = std::make_unique<SliderEx>(Slider::LinearVertical, Slider::NoTextBox);
    leftSlider->setRange(.0, 100., 0);
    rightSlider->setRange(.0, 100., 0);
    addAndMakeVisible(leftSlider.get());
    addAndMakeVisible(rightSlider.get());
}

EditorWindow::~EditorWindow() {
    leftSlider = nullptr;
    rightSlider = nullptr;
}

void EditorWindow::showEditor(void *hwnd) {
    setVisible(true);
    setOpaque(true);
    setSize(500, 350);
    addToDesktop(ComponentPeer::StyleFlags::windowIsResizable, hwnd);
}

void EditorWindow::hideEditor() {
    removeFromDesktop();
}

void *EditorWindow::getWindowHandle() {
    ComponentPeer *peer = getPeer();
    if (peer) {
        return peer->getNativeHandle();
    } else {
        return NULL;
    }
}

//==============================================================================
void EditorWindow::paint(Graphics &g) {
    g.fillAll(Colour(0xff323e44));
}

void EditorWindow::resized() {
    static int width = 30;
    juce::Rectangle<int> b = getBounds();
    juce::Rectangle<int> left = b.removeFromLeft(b.getWidth() / 2);
    if (left.getWidth() > width) {
        left.reduce((left.getWidth() - width) / 2, 0);
        b.reduce((left.getWidth() - width) / 2, 0);
    }
    leftSlider->setBounds(left);
    rightSlider->setBounds(b);
}

void EditorWindow::linkControllers(ParamManager &paramManager) {
    paramManager.bindControllerComponent(prmGainLeft, leftSlider.get());
    paramManager.bindControllerComponent(prmGainRight, rightSlider.get());
}
