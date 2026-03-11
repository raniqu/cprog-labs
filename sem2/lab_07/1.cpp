#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <algorithm>

template <class T>
class vector {
public:
    vector() : vector_data(nullptr), vector_size(0), vector_capacity(0) {}

    vector(size_t n, const T& value) : vector_size(n), vector_capacity(n) {
        vector_data = new T[n];
        for (size_t i = 0; i < n; i++) vector_data[i] = value;
    }

    vector(const vector& vec) : vector_size(vec.vector_size), vector_capacity(vec.vector_capacity) {
        vector_data = new T[vector_capacity];
        for (size_t i = 0; i < vector_size; i++) vector_data[i] = vec.vector_data[i];
    }

    ~vector() { delete[] vector_data; }

    vector& operator=(const vector& vec) {
        if (this != &vec) {
            delete[] vector_data;
            vector_capacity = vec.vector_capacity;
            vector_size = vec.vector_size;
            vector_data = new T[vector_capacity];
            for (size_t i = 0; i < vector_size; i++) vector_data[i] = vec.vector_data[i];
        }
        return *this;
    }

    T& operator[](size_t index) {
        if (index >= vector_size) throw std::out_of_range("Index out of range");
        return vector_data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= vector_size) throw std::out_of_range("Index out of range");
        return vector_data[index];
    }

    T& at(size_t index) {
        if (index >= vector_size) throw std::out_of_range("Index out of range");
        return vector_data[index];
    }

    const T& at(size_t index) const {
        if (index >= vector_size) throw std::out_of_range("Index out of range");
        return vector_data[index];
    }

    T& front() {
        if (vector_size == 0) throw std::out_of_range("Vector is empty");
        return vector_data[0];
    }

    T& back() {
        if (vector_size == 0) throw std::out_of_range("Vector is empty");
        return vector_data[vector_size - 1];
    }

    T* data() { return vector_data; }
    T* begin() { return vector_data; }
    T* end() { return vector_data + vector_size; }
    const T* begin() const { return vector_data; }
    const T* end() const { return vector_data + vector_size; }

    bool empty() const { return vector_size == 0; }
    size_t size() const { return vector_size; }
    size_t capacity() const { return vector_capacity; }

    void reserve(size_t new_capacity) {
        if (new_capacity <= vector_capacity) return;
        T* new_data = new T[new_capacity];
        for (size_t i = 0; i < vector_size; i++) new_data[i] = vector_data[i];
        delete[] vector_data;
        vector_data = new_data;
        vector_capacity = new_capacity;
    }

    void clear() { vector_size = 0; }

    void push_back(const T& value) {
        if (vector_size >= vector_capacity) {
            size_t new_cap = (vector_capacity == 0) ? 1 : vector_capacity * 2;
            reserve(new_cap);
        }
        vector_data[vector_size++] = value;
    }

    void pop_back() {
        if (vector_size == 0) throw std::out_of_range("Vector is empty");
        vector_size--;
    }

    void swap(vector& other) {
        std::swap(vector_data, other.vector_data);
        std::swap(vector_size, other.vector_size);
        std::swap(vector_capacity, other.vector_capacity);
    }

private:
    T* vector_data;
    size_t vector_size;
    size_t vector_capacity;
};

int main() {
    return 0;
}