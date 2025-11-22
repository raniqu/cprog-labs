#include <iostream>

int main() {
    long long pr = 1;
    for (int i{8}; i < 16; i++) {
        pr *= i;
    }
    std::cout << "from 8 to 15 " << pr << std::endl;

    int a;
    std::cout << "enter a " << std::endl;
    std::cin >> a;
    pr = 1;
    for (int i{a}; i < 21; i++) {
        pr *= i;
    }
    std::cout << "from a to 20 " << pr << std::endl;

    int b;
    std::cout << "enter b, but b >= a" << std::endl;
    std::cin >> b;

    pr = 1;
    for (int i{1}; i < (b+1); i++) {
        pr *= i;
    }
    std::cout << "from 1 to b " << pr << std::endl;
    if (a <= b){
        pr = 1;
        for (int i{a}; i < (b+1); i++) {
            pr *= i;
        }
        std::cout << "from a to b " << pr << std::endl;
    }

}