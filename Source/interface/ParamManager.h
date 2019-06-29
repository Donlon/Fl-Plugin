#pragma once

#include <JuceHeader.h>

#include <iostream>
#include <vector>
#include <map>
#include <ObjIdlbase.h>

class Param;

class TCPPFruityPlug;

struct IStream;

class ParamManager {
    static const int version = 0;

    std::vector<Param *> paramList;
    std::map<Component *, Param *> paramComponentMap;
    std::map<int, Param *> paramIdMap;
    TCPPFruityPlug *fruityPlug;

    bool isPreviousVersionOutOfDate = false;

public:
    ParamManager(TCPPFruityPlug *fruityPlug);

    ~ParamManager();

    Param &addParam(int id, const char *name, int defaultValue);

    void bindControllerComponent(int id, Component *component);

    void bindControllerComponent(int id, Slider *slider);

    Param &getParamByPosition(int pos);

    Param *getParamById(int id);

    Param *getParam(Component *index);

    int getValue(int index);

    void setValue(int index, int value, int isActive = true);

    void notifyHostValueChanged(int index, int value);

    std::vector<Param *> &getParamList();

    void saveToStream(IStream &stream);

    void loadFromStream(IStream &stream);
};
