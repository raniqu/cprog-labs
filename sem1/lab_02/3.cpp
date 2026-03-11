#include <iostream>

int main() {
    for (int i {1}; i < 10; i++) {
        std::cout << i << " * " << 7 << " = " << 7*i << std::endl;
    }
    int n;
    std::cin >> n;
    for (int i {1}; i < 10; i++) {
        std::cout << i << " * " << n << " = " << n*i << std::endl;
    }


}
