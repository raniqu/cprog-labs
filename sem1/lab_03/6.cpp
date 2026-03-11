
#include <string>

bool first_is_longer(const std::string& name_one, const std::string& name_two) {
    if (name_one.size() > name_two.size()) {
        return true;
    }
    return false;
}
