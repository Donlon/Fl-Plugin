#include <string>
#include <functional>

namespace ValueFormatters {
    std::function<std::string(float)> percentageFormatter = [](float val) -> std::string {
        return std::to_string((int) (val * 100)) + "%";
    };
}