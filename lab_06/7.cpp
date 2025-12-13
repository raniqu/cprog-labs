
#include "lab.hpp"

void reverseNum(std::list<int>& nums) {
    for (auto it = nums.begin(); it != nums.end(); ++it) {
        if (*it != 0) {
            nums.insert(it, *it*(-1));
        }
    }
}
