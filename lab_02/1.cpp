#include <iostream>

int main() {
    int x, y, z;
    std::cin >> x >> y >> z;
    bool a1 = ((x%2 != 0) && (y%2 != 0));
    if (a1 == 1) {
        std::cout << "condition is true" << std::endl;
    }
    else {
        std::cout << "condition is false" << std::endl;
    }

    bool a2 = (((x < 20) + (y < 20)) == 1);
    if (a2 == 1) {
        std::cout << "condition is true" << std::endl;
    }
    else {
        std::cout << "condition is false" << std::endl;
    }
    bool a3 = ((x == 0) || (y == 0));
    if (a3 == 1) {
        std::cout << "condition is true" << std::endl;
    }
    else {
        std::cout << "condition is false" << std::endl;
    }
    bool a4 = ((x < 0) && (y < 0) && (z < 0));
    if (a4 == 1) {
        std::cout << "condition is true" << std::endl;
    }
    else {
        std::cout << "condition is false" << std::endl;
    }
    bool a5 = (((x %5 == 0) + (y % 5 == 0) + (z % 5 == 0)) == 1);
    if (a5 == 1) {
        std::cout << "condition is true" << std::endl;
    }
    else {
        std::cout << "condition is false" << std::endl;
    }
    bool a6 = ((x > 100) || (y > 100) || (z > 100));
    if (a6 == 1) {
        std::cout << "condition is true" << std::endl;
    }
    else {
        std::cout << "condition is false" << std::endl;
    }
}