
#include <numeric>

#include "lab04.h"

float mean(const std::vector<float>& data) {
    if (data.empty()) {
        return 0.0;
    }
    float sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}