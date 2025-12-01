#include <limits>

#include "lab04.h"

std::pair<float, float> minMax(const std::vector<float>& data) {
    if (data.empty()) {
        return {std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};
    }
    float minV = data[0];
    float maxV = data[0];
    for (float item : data) {
        minV = std::min(minV, item);
        maxV = std::max(maxV, item);
    }
    return {minV, maxV};
}