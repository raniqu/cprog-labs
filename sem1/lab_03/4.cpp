#include <iostream>
#include <vector>

void remove_negative(std::vector<int>& input) {
    for (size_t i = 0; i < input.size(); i++) {
        if (input[i] < 0){
            input.erase(input.begin() + i);
            return;
        }
    }
}

void remove_last_even(std::vector<int>& input) {
    for (size_t i = input.size() - 1; i < input.size() && i >= 0; i--) {
        if (input[i] % 2 == 0) {
            input.erase(input.begin() + i);
            return;
        }
    }
}
