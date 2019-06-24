#pragma once

#include <string>
#include <functional>

class Param {
public:
    size_t pos;
    int id;
    std::string name;
    std::string desc;
    int value; // cached value, managed by ParamManager
    int defaultValue;

    Param(int id, int defaultValue);

    // Only affects GUI/Controller, won't feedback to host.
    std::function<void(int)> paramSetter;

    std::function<int()> paramGetter;

    // return true if desiring to invalidate the change
    std::function<bool(int)> onChangeListener;

    std::function<std::string(int)> valueFormatter;
};
