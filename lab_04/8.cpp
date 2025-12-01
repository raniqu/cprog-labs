#include "lab04.h"


std::string join(const std::vector<std::string>& data, const std::string& sep) {
    std::string res;
    if (data.empty()) {
        return res;
    }
    res = data[0];
    for (size_t i = 1; i < data.size(); ++i) {
        res += sep;
        res += data[i];
    }
    return res;
}

