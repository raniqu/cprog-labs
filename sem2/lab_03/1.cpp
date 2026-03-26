#include <iostream>

// 1
template<typename T>
class MyUnique {
private:
    T* p = nullptr;

public:
    explicit MyUnique(T* ptr = nullptr) : p(ptr) {}

    ~MyUnique() {
        delete p;
    }

    MyUnique(const MyUnique& other) = delete;

    MyUnique(MyUnique&& other) noexcept : p(other.p) {
        other.p = nullptr;
    }

    MyUnique& operator=(const MyUnique& other) = delete;

    MyUnique& operator=(MyUnique&& other) noexcept {
        if (this != &other) {
            delete p;
            p = other.p;
            other.p = nullptr;
        }
        return *this;
    }

    T* get() const {
        return p;
    }

    T& operator*() {
        if (!p) throw std::runtime_error("Dereferencing null pointer");
        return *p;
    }

    T* operator->() {
        return p;
    }
};

// 2
template<typename T>
class MyShared {
private:
    T* p = nullptr;
    int* ref_count = nullptr;

    void release() {
        if (ref_count) {
            (*ref_count)--;
            if (*ref_count == 0) {
                delete p;
                delete ref_count;
            }
        }
    }

public:
    explicit MyShared(T* ptr = nullptr) : p(ptr), ref_count(new int(1)) {}

    ~MyShared() {
        release();
    }

    MyShared(const MyShared& other) : p(other.p), ref_count(other.ref_count) {
        if (ref_count) {
            (*ref_count)++;
        }
    }

    MyShared(MyShared&& other) noexcept : p(other.p), ref_count(other.ref_count) {
        other.p = nullptr;
        other.ref_count = nullptr;
    }

    MyShared& operator=(const MyShared& other) {
        if (this != &other) {
            release();
            p = other.p;
            ref_count = other.ref_count;
            if (ref_count) {
                (*ref_count)++;
            }
        }
        return *this;
    }

    MyShared& operator=(MyShared&& other) noexcept {
        if (this != &other) {
            release();
            p = other.p;
            ref_count = other.ref_count;
            other.p = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    T* get() const {
        return p;
    }

    T& operator*() {
        return *p;
    }

    T* operator->() {
        return p;
    }
};

int main() {
    std::cout << "=== MyUnique ===" << std::endl;

    // Конструктор
    MyUnique<int> ptr1(new int(42));
    std::cout << "ptr1 value: " << *ptr1 << std::endl;
    std::cout << "ptr1 get(): " << ptr1.get() << std::endl;

    // Перемещение
    MyUnique<int> ptr2 = std::move(ptr1);
    std::cout << "ptr2 value: " << *ptr2 << std::endl;
    std::cout << "ptr1 get(): " << ptr1.get() << " (nullptr)" << std::endl;

    // Оператор присваивания перемещением
    MyUnique<int> ptr3;
    ptr3 = std::move(ptr2);
    std::cout << "ptr3 value: " << *ptr3 << std::endl;

    // Операторы * и ->
    struct Test {
        int x = 10;
        void print() { std::cout << "x = " << x << std::endl; }
    };

    MyUnique<Test> ptr4(new Test());
    std::cout << "ptr4->x: " << ptr4->x << std::endl;
    (*ptr4).print();
    std::cout << "\n=== MyShared ===" << std::endl;

    // Конструктор
    MyShared<int> shared1(new int(100));
    std::cout << "shared1 value: " << *shared1 << std::endl;

    // Копирование
    MyShared<int> shared2 = shared1;
    std::cout << "shared2 value: " << *shared2 << std::endl;

    // Оператор присваивания копированием
    MyShared<int> shared3;
    shared3 = shared1;
    std::cout << "shared3 value: " << *shared3 << std::endl;

    // Перемещение
    MyShared<int> shared4 = std::move(shared1);
    std::cout << "shared4 value: " << *shared4 << std::endl;

    // Операторы * и ->
    MyShared<Test> shared5(new Test());
    std::cout << "shared5->x: " << shared5->x << std::endl;
    (*shared5).print();

    return 0;
}

