#include  "lab.hpp"

int wordsCounter(const std::string& str) {
    int result = 0;
    bool start_word = false;
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (*it != ' ' && *it != ',' && *it != '.') {
            start_word = true;
        }
        else {
            if (start_word == true) {
                ++result;
                start_word = false;
            }
        }
    }
    if (start_word == true) {
        return result + 1;
    }
    return result;
}
