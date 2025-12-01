
#include "lab04.h"


std::string replace(const std::string& str, const std::string& old, const std::string& new_string) {
    if (old.empty()) {
        return str;
    }
    std::string res = str;
    size_t pos = res.find(old);

    while (pos != std::string::npos) {
        res.erase(pos, old.length());
        res.insert(pos, new_string);
        pos = res.find(old, pos);
    }
    return res;
}
