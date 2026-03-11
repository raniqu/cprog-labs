#include <cstring>
#include "header.hpp"

char* CopyString(const char* str) {
    if (str == nullptr) {
        return nullptr;
    }

    size_t len = 0;
    const char* ptr = str;

    while (*ptr != '\0') {
        ++len;
        ++ptr;
    }

    char* copy = new char[len + 1];

    memcpy(copy, str, len + 1);

    return copy;
}


char* ConcatinateStrings(const char* a, const char* b) {
    if (a == nullptr && b == nullptr) {
        return nullptr;
    }
    if (a == nullptr){a = "";}
    if (b == nullptr){b = "";}

    size_t len_a = 0;
    const char* ptr_a = a;

    while (*ptr_a != '\0') {
        ++len_a;
        ++ptr_a;
    }

    size_t len_b = 0;
    const char* ptr_b = b;

    while (*ptr_b != '\0') {
        ++len_b;
        ++ptr_b;
    }

    size_t total_len = len_a + len_b + 1;
    char* result = new char[total_len];

    memcpy(result, a, len_a);
    memcpy(result + len_a, b, len_b);

    result[total_len - 1] = '\0';

    return result;
}


