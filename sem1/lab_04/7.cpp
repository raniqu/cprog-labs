#include "lab04.h"


std::vector<std::string> split(const std::string& data, char sep) {
    std::vector<std::string> res;

    size_t start = 0;
    size_t end = data.find(sep);

    while (end != std::string::npos) {
        res.push_back(data.substr(start, end - start));

        start = end + 1;
        end = data.find(sep, end + 1);
    }
    if (start < data.size()) {
        res.push_back(data.substr(start));
    }

    return res;
}
