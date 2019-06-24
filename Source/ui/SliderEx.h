#pragma once

#include <JuceHeader.h>

class SliderEx : public Slider {
public:
    SliderEx();

    explicit SliderEx(const String &componentName);

    SliderEx(SliderStyle style, TextEntryBoxPosition textBoxPosition);;

    std::function<bool(const MouseEvent &)> onClick;

    void mouseDown(const MouseEvent &e) override;

    void mouseUp(const MouseEvent &e) override;
};