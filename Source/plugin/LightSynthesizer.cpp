#include <algorithm>
#include <thread>

#include "LightSynthesizer.h"

LightSynthesizer::LightSynthesizer(int pixelCount) : pixelCount(pixelCount) {
    buffer.resize(pixelCount);
    updatingStatus = Stopped;
    std::thread th([]() {

    });
    th.detach();
}

LightSynthesizer::~LightSynthesizer() = default;

void LightSynthesizer::setUpdatingInterval(int interval) {
    updatingInterval = interval;
}

void LightSynthesizer::onParamChange(Param param, float val) {
    if (param == Brightness) {
        brightness_v = (uint8_t) std::min((unsigned int) (val * 256.f), 255u);
    }
}

void LightSynthesizer::startAutoUpdate() {
    if (updatingStatus != Updating) {
        updatingStatus = Updating;
        // new thread
    }
}

void LightSynthesizer::stopAutoUpdate() {
    if (updatingStatus != Stopped) {
        updatingStatus = Stopped;
    }
}

// TODO: run in a new thread
void LightSynthesizer::triggerUpdate() {
    renderFrame();
    onCanvasUpdate(*this);
}

std::basic_string<rgb888_t> &LightSynthesizer::getBuffer() {
    return buffer;
}

void LightSynthesizer::renderFrame() {
    for (int i = 0; i < pixelCount; i++) {
        rgb888_t &px = buffer[i];
        px.r = brightness_v;
        px.g = brightness_v;
        px.b = brightness_v;
    }
}
