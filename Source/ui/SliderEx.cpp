#include "SliderEx.h"
#include "utils/CursorUtils.h"

SliderEx::SliderEx() : Slider() {
    //this->getVelocityBasedMode();
    this->setSliderSnapsToMousePosition(false);
}

SliderEx::SliderEx(const String &componentName) : Slider(componentName) {
    this->setSliderSnapsToMousePosition(false);
}

SliderEx::SliderEx(Slider::SliderStyle style, Slider::TextEntryBoxPosition textBoxPosition)
        : Slider(style, textBoxPosition) {
    this->setSliderSnapsToMousePosition(false);
}

void SliderEx::mouseDown(const MouseEvent &e) {
    if (!(onClick && onClick(e))) {
        Slider::mouseDown(e);
    }

    if (e.mods.isLeftButtonDown()) {
        CursorUtils::hideCursorAndSavePos();
    }
}

void SliderEx::mouseUp(const MouseEvent &e) {
    if (e.mods.isLeftButtonDown()) {
        CursorUtils::restoreCursor();
    }
}
