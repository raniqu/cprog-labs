
#include <iostream>
#include <stdexcept>
#include <cmath>

class InvalidProgressionException : public std::invalid_argument {
private:
    double firstElement;
    double denominator;
    int size;
    double* array;

public:
    InvalidProgressionException(const std::string& message, double first, double denom, int sz, double* arr)
        : std::invalid_argument(message), firstElement(first), denominator(denom), size(sz) {
        array = new double[size];
        for (int i = 0; i < size; ++i) {
            array[i] = arr[i];
        }
    }

    ~InvalidProgressionException() {
        delete[] array;
    }

    void printData() const {
        std::cout << "=== Invalid object data ===" << std::endl;
        std::cout << "First element: " << firstElement << std::endl;
        std::cout << "Denominator: " << denominator << std::endl;
        std::cout << "Size: " << size << std::endl;
        std::cout << "Array: ";
        for (int i = 0; i < size; ++i) {
            std::cout << array[i];
            if (i < size - 1) std::cout << ", ";
        }
        std::cout << std::endl;
        std::cout << "Error: " << what() << std::endl;
        std::cout << "===========================" << std::endl;
    }
};

class GeometricProgressionArray {
private:
    double firstElement;
    double denominator;
    double* array;
    int size;

    void validate() {
        if (size <= 0) {
            throw InvalidProgressionException("Size must be positive", firstElement, denominator, size, array);
        }
        if (denominator == 0) {
            throw InvalidProgressionException("Denominator cannot be zero", firstElement, denominator, size, array);
        }
        for (int i = 0; i < size; ++i) {
            double expected = firstElement * pow(denominator, i);
            if (fabs(array[i] - expected) > 1e-9) {
                throw InvalidProgressionException("Array is not a geometric progression", firstElement, denominator, size, array);
            }
        }
    }

public:
    GeometricProgressionArray(double first, double denom, int sz, double* arr)
        : firstElement(first), denominator(denom), size(sz) {
        array = new double[size];
        for (int i = 0; i < size; ++i) {
            array[i] = arr[i];
        }
        validate();
    }

    GeometricProgressionArray(const GeometricProgressionArray& other)
        : firstElement(other.firstElement), denominator(other.denominator), size(other.size) {
        array = new double[size];
        for (int i = 0; i < size; ++i) {
            array[i] = other.array[i];
        }
    }

    ~GeometricProgressionArray() {
        delete[] array;
    }

    double getNthElement(int n) const {
        if (n < 1 || n > size) throw std::out_of_range("Index out of range");
        return firstElement * pow(denominator, n - 1);
    }

    void print() const {
        std::cout << "First element: " << firstElement << ", Denominator: " << denominator << ", Size: " << size << std::endl;
        std::cout << "Array: ";
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::cout << "=== Valid progression ===" << std::endl;
    try {
        double arr[] = {2, 4, 8, 16};
        GeometricProgressionArray valid(2, 2, 4, arr);
        valid.print();
        std::cout << "3rd element: " << valid.getNthElement(3) << std::endl;
    }
    catch (const InvalidProgressionException& e) {
        e.printData();
    }

    std::cout << "\n=== Invalid progression (wrong element) ===" << std::endl;
    try {
        double arr[] = {3, 9, 27, 80};
        GeometricProgressionArray invalid(3, 3, 4, arr);
        invalid.print();
    }
    catch (const InvalidProgressionException& e) {
        e.printData();
    }

    try {
        double arr[] = {5, 0, 0, 0};
        GeometricProgressionArray zeroDenom(5, 0, 4, arr);
        zeroDenom.print();
    }
    catch (const InvalidProgressionException& e) {
        e.printData();
    }

    return 0;
}