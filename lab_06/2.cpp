#include "lab.hpp"

std::vector<int>::iterator findInSorted(std::vector<int>::iterator first, std::vector<int>::iterator last, int el) {
    for (auto it = first; it != last; ++it) {
        if (*it == el) {
            return it;
        }
        if (*it > el) {
            break;
        }
    }
    return last;
}