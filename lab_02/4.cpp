#include <iostream>

int main() {
    long long pr = 1;
    for (int i{8}; i < 16; i++) {
        pr *= i;
    }
    std::cout << pr << std::endl;

    int a;
    std::cin >> a;
    pr = 1;
    for (int i{a}; i < 21; i++) {
        pr *= i;
    }
    std::cout << pr << std::endl;

    int b;
    std::cin >> b;

    pr = 1;
    for (int i{1}; i < (b+1); i++) {
        pr *= i;
    }
    std::cout << pr << std::endl;

    pr = 1;
    for (int i{a}; i < (b+1); i++) {
        pr *= i;
    }
    std::cout << pr << std::endl;

}