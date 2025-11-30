#include <iostream>
#include <vector>
#include <numeric>
#include <stdexcept>

int sum(const std::vector<int>& input) {
    return std::accumulate(input.begin(), input.end(), 0);
}

int square_sum(const std::vector<int>& input) {

    int res = 0;
    for (int item : input) {
        res += item*item;
    }
    return res;
}

int sum_six(const std::vector<int>& input) {
    if (input.size() < 6) {
        throw std::length_error("less than 6 elements");
    }
    auto end = std::next(input.begin(), 6);
    return std::accumulate(input.begin(), end, 0);
}

int sum_k(const std::vector<int>& input, int k1, int k2) {
    if ((k1 > k2) || (k1 < 0) || (k2 >= input.size())) {
        throw std::out_of_range("incorrect indexes");
    }
    return std::accumulate(input.begin()+k1, input.begin()+k2+1, 0);
}

double mean(const std::vector<int>& input) {
    if (input.empty()) {
        throw std::runtime_error("empty array");
    }
    return (1.0 * sum(input)) / input.size();
}

double mean_k(const std::vector<int>& input, int s1, int s2) {
    if ((s1 > s2) || (s1 < 0) || (s2 >= input.size())) {
        throw std::out_of_range("incorrect indexes");
    }
    return (1.0 * sum_k(input, s1, s2)) / (s2-s1+1);
}
