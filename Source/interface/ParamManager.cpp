#include <cassert>

#include "ParamManager.h"
#include "Param.h"
#include "../ui/SliderEx.h"

#include "../fpsdk/fp_cplug.h"

ParamManager::ParamManager(TCPPFruityPlug *fruityPlug) : fruityPlug(fruityPlug) {
    paramList.reserve(10);
}

ParamManager::~ParamManager() {
    for (Param *&item : paramList) {
        delete item;
    }
}

Param &ParamManager::addParam(int id, const char *name, float defaultValue) {
    auto *param = new Param(id, defaultValue);
    param->name.assign(name);
    param->desc.assign(name);
    param->pos = paramList.size();
    param->defaultValue = defaultValue;

    paramList.push_back(param);
    paramIdMap.insert(std::pair<int, Param *>(id, param));

    return *param;
}

void ParamManager::bindControllerComponent(int id, Slider *slider) {
    Param &param = *getParamById(id);

    param.paramGetter = [slider]() -> float {
        return (float) (slider->getValue() / 100.);
    };
    param.paramSetter = [slider](float value) {
        slider->setValue((double) value * 100.f);
    };

    size_t pos = param.pos;
    slider->onValueChange = [this, pos, slider]() {
        Param &param = *paramList[pos];
        float newValue = param.paramGetter();
        if (param.value != newValue) {
            if (param.onChangeListener && param.onChangeListener(newValue)) {
                return;
            }
            param.value = newValue;
            notifyHostValueChanged((int) pos, newValue);
        }
    };

    param.paramSetter(param.defaultValue);

    if (auto sliderEx = dynamic_cast<SliderEx *>(slider)) {
        sliderEx->onClick = [this, pos](const MouseEvent &e) -> bool {
            if (e.mods.isRightButtonDown()) {
                PopupMenu m;
                int n = 0;
                while (true) {
                    if (auto menuEntry = (PParamMenuEntry)
                            fruityPlug->PlugHost->Dispatcher(fruityPlug->HostTag, FHD_GetParamMenuEntry, pos, n)) {
                        if (!menuEntry) {
                            break;
                        }
                        bool enabled = !(menuEntry->Flags & FHP_Disabled);
                        bool ticked = menuEntry->Flags & FHP_Checked;
                        bool isSeparator = strcmp(menuEntry->Name, "-") == 0;
                        bool isSelectionHeader = *menuEntry->Name == '-'; // or isSeparator
                        int id = DefaultMenuID + n;
                        if (isSeparator) {
                            m.addSeparator();
                        } else if (isSelectionHeader) {
                            m.addSectionHeader(menuEntry->Name + 1);
                        } else {
                            String title = menuEntry->Name;
                            m.addItem(id, title.removeCharacters("&"), enabled, ticked);
                        }
                        n++;
                    } else {
                        break;
                    }
                }
                int result = m.show();
                if (result) {
                    fruityPlug->PlugHost->Dispatcher(fruityPlug->HostTag, FHD_ParamMenu, pos, result - DefaultMenuID);
                }
                return true;
            } else {
                return false;
            }
        };
    }

    paramComponentMap.insert(std::pair<Component *, Param *>(slider, &param));
}

Param &ParamManager::getParamByPosition(int pos) {
    assert(pos < paramList.size());
    assert(paramList[pos] != nullptr);

    return *paramList[pos];
}

Param *ParamManager::getParamById(int id) {
    Param *param = nullptr;
    auto it = paramIdMap.find(id);
    if (it != paramIdMap.end()) {
        param = it->second;
    } else {
        assert(param != nullptr);
    }
    return param;
}

Param *ParamManager::getParam(Component *index) {
    auto it = paramComponentMap.find(index);
    if (it != paramComponentMap.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

float ParamManager::getValue(int index) {
    Param &param = *paramList[index];
    if (param.paramGetter) {
        return param.paramGetter();
    }
    return param.value;
}

void ParamManager::setValue(int pos, float value, int isActive) {
    Param &param = *paramList[pos];
    if (param.value != value) {
        if (param.onChangeListener && param.onChangeListener(value)) {
            return;
        }

        param.value = value;
        if (param.paramSetter) {
            param.paramSetter(value);
        }
        if (isActive) {
            notifyHostValueChanged(pos, value);
        }
    }
}

void ParamManager::notifyHostValueChanged(int index, float value) {
    fruityPlug->PlugHost->OnParamChanged(fruityPlug->HostTag, index, (int) (value * 100.f));
}

std::vector<Param *> &ParamManager::getParamList() {
    return paramList;
}

void ParamManager::saveToStream(IStream &stream) {
    ULONG written = 0;
    stream.Write(&version, sizeof(int), &written);
    int size = (int) paramList.size();
    stream.Write(&size, sizeof(int), &written);
    for (Param *param : paramList) {
        stream.Write(&param->id, sizeof(int), &written);
        stream.Write(&param->value, sizeof(float), &written);
    }
}

void ParamManager::loadFromStream(IStream &stream) {
    ULONG read = 0;
    int lastVersion;
    stream.Read(&lastVersion, sizeof(int), &read);
    if (lastVersion >= version) {
        isPreviousVersionOutOfDate = true;
        return;
    }
    isPreviousVersionOutOfDate = false;
    int size;
    stream.Read(&size, sizeof(int), &read);
    for (int i = 0; i < size; i++) {
        int id;
        float value;
        stream.Read(&id, sizeof(int), &read);
        stream.Read(&value, sizeof(float), &read);
        setValue(id, value, true);
    }
}
