#include "lab04.h"


int argmax(const std::vector<float>& data) {
    if (data.empty()) {
        return -1;
    }
    int idmax = 0;
    float elemmax = data[0];

    for (size_t i = 1; i < data.size(); ++i) {
        if (data[i] > elemmax) {
            elemmax = data[i];
            idmax = i;
        }
    }
    return idmax;
}
