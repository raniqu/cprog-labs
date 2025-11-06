#include <iostream>

int main() {
    int x, y, z;
    std::cin >> x >> y >> z;
    bool a1 = ((x%2 != 0) && (y%2 != 0));
    bool a2 = (((x < 20) + (y < 20)) == 1);
    bool a3 = ((x == 0) || (y == 0));
    bool a4 = ((x < 0) && (y < 0) && (z < 0));
    bool a5 = (((x %5 == 0) + (y % 5 == 0) + (z % 5 == 0)) == 1);
    bool a6 = ((x > 100) || (y > 100) || (z > 100));
    if ((a1 + a2 + a3 + a4 + a5 + a6) == 6) {
        std::cout << "condition is true" << std::endl;
    }
    else {
        std::cout << "condition is false" << std::endl;
    }

}
