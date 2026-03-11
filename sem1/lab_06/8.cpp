#include  "lab.hpp"

void plusesDeleter(std::vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); ) {
        if (*it > 0) {
            it = v.erase(it);
        }
        else {
            ++it;
        }
    }
}