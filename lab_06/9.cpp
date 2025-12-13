#include "lab.hpp"
void Sort(std::list<int>& nums) {
    if (nums.size() < 2){
        return;
    }
    size_t finish = nums.size() - 1;
    auto end = std::prev(nums.end());

    for (size_t i = 0; i < finish; ++i){

        for (auto it = nums.begin(); it != end; ++it) {
            auto next_it = std::next(it);
            if (*it < *next_it) {
                std::swap(*it, *next_it);
            }
        }
        --end;
    }
}