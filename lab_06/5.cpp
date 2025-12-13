
#include "lab.hpp"

std::vector<std::string> uniqueWords(const std::string& str) {
    std::map<std::string, int> map_counter = wordsMapCounter(str);

    std::vector<std::string> result;
    result.reserve(map_counter.size());
    for (const auto& elem : map_counter) {
        result.push_back(elem.first);
    }
    return result;
}
