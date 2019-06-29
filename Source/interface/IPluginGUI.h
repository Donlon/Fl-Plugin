#pragma once

class IPluginGUI {
public:
    virtual void showEditor(void *parent) = 0;

    virtual void hideEditor() = 0;

    virtual void *getWindowHandle() = 0;
};