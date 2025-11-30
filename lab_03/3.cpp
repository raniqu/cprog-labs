#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>



void swap_el(std::vector<int>& input) {
    if (input.size() < 6) {
        throw std::length_error("less than 6 elements");
    }
    for (int i = 0; i < 3; i++) {
        std::swap(input[i], input[input.size() - 3 + i]);
    }
}
