#include <string>
#include <functional>

namespace ValueFormatters {
    std::function<std::string(int)> precentageFormatter = [](int val) -> std::string {
        return std::to_string(val) + "%";
    };
}