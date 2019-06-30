#pragma once

#include <cstdint>
#include <functional>
#include <string>

struct rgb888_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class LightSynthesizer {
    int pixelCount;
    std::basic_string<rgb888_t> buffer;

    uint8_t brightness_v = 0;

    enum {
        Updating,
        Stopped
    } updatingStatus;

    int updatingInterval = 50;

public:
    enum Param {
        Brightness
    };

    explicit LightSynthesizer(int pixelCount);

    ~LightSynthesizer();

    void setUpdatingInterval(int interval);

    void onParamChange(Param param, float val);

    void startAutoUpdate();

    void stopAutoUpdate();

    void triggerUpdate();

    std::basic_string<rgb888_t> &getBuffer();

    std::function<void(LightSynthesizer &)> onCanvasUpdate;

private:
    void renderFrame();
};

