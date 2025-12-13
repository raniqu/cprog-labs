
#include "lab.hpp"

std::map<std::string, int> wordsMapCounter(const std::string& str) {
    std::map<std::string, int> result;
    std::string s;
    for (size_t i = 0; i != str.length(); ++i) {
        if (str[i] != ' ' && str[i] != ',' && str[i] != '.') {
            s += str[i];
        }
        else {
            if (!s.empty()) {
                ++result[s];
                s.clear();
            }
        }
    }
    if (s.empty()) {
        return result;
    }
    ++result[s];
    return result;
}