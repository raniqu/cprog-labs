#include <iostream>
#include <string>

bool name_is_even(const std::string& name) {
    if (name.length() % 2 == 0) {
        return 1;
    }
    return 0;
}
