// 5 вариант

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include <chrono>

void insertion_sort(std::vector<double>& arr, int begin, int end) {
    for (int i = begin + 1; i < end; ++i) {
        double key = arr[i];
        int j = i - 1;
        while (j >= begin && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void print_lock_guard(const std::string& name, double value, std::mutex& mtx) {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << name;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << " " << value << std::endl;
}

void print_unique_lock(const std::string& name, double value, std::mutex& mtx) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << name;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << " " << value << std::endl;
}

void print_array(const std::string& name, const std::vector<double>& arr, std::mutex& mtx, bool use_lock_guard = true) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (use_lock_guard)
            print_lock_guard(name, arr[i], mtx);
        else
            print_unique_lock(name, arr[i], mtx);
    }
}

void worker(const std::string& name,
            std::vector<double>& arr,
            int start, int end,
            std::mutex& print_mtx,
            std::mutex& count_mtx,
            std::condition_variable& cv,
            int& finished_count,
            bool use_lock_guard) {
    insertion_sort(arr, start, end);
    print_array(name, arr, print_mtx, use_lock_guard);

    {
        std::lock_guard<std::mutex> lock(count_mtx);
        ++finished_count;
    }
    cv.notify_one();
}

void fill_random(std::vector<double>& arr) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0, 100.0);
    for (auto& x : arr) x = dist(gen);
}

int main() {
    int N;
    std::cout << "Enter array size: ";
    std::cin >> N;
    std::vector<double> data(N);
    fill_random(data);

    std::cout << "Initial array:\n";
    for (auto x : data) std::cout << x << " ";
    std::cout << std::endl << std::endl;

    std::mutex print_mtx;
    std::mutex count_mtx;
    std::condition_variable cv;
    int finished_count = 0;

    int mid = N / 2;

    std::thread t1(worker, "thread1", std::ref(data), 0, mid,
                   std::ref(print_mtx), std::ref(count_mtx), std::ref(cv), std::ref(finished_count), true);
    std::thread t2(worker, "thread2", std::ref(data), mid, N,
                   std::ref(print_mtx), std::ref(count_mtx), std::ref(cv), std::ref(finished_count), true);

    for (int step = 0; step < 2; ++step) {
        std::unique_lock<std::mutex> lock(count_mtx);
        cv.wait(lock, [&finished_count, old = finished_count] { return finished_count > old; });
        std::cout << "Total finished: " << finished_count << std::endl;
    }

    std::thread t3(worker, "thread3", std::ref(data), 0, N,
                   std::ref(print_mtx), std::ref(count_mtx), std::ref(cv), std::ref(finished_count), false);

    {
        std::unique_lock<std::mutex> lock(count_mtx);
        cv.wait(lock, [&finished_count, old = finished_count] { return finished_count > old; });
        std::cout << "Total finished: " << finished_count << std::endl;
    }

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Work done." << std::endl;
    return 0;
}