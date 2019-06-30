#pragma once

#include <string>
#include <functional>

class Param {
public:
    size_t pos = 0;
    int id;
    std::string name;
    std::string desc;
    float value; // cached value, managed by ParamManager
    float defaultValue;

    Param(int id, float defaultValue);

    // Only affects GUI/Controller, won't feedback to host.
    std::function<void(float)> paramSetter;

    std::function<float()> paramGetter;

    // return true if desiring to invalidate the change
    std::function<bool(float)> onChangeListener;

    std::function<std::string(float)> valueFormatter;
};
