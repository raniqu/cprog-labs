#include "lab04.h"

void sort(std::vector<float>& data) {
    if (data.empty()) return;

    size_t n = data.size();
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - 1 - i; ++j) {
            if (data[j] < data[j+1]) {
                std::swap(data[j], data[j+1]);
            }
        }
    }
}

