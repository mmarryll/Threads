#include "Solver.h"
#include "ThreadSafeStack.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <atomic>

Solver::Solver(const std::string& filename, size_t thread_count)
    : filename_(filename), thread_count_(thread_count) {
}

static bool IsPrime(int value) {
    if (value <= 1) {
        return false;
    }
    for (int i = 2; i * i <= value; ++i) {
        if (value % i == 0) {
            return false;
        }
    }
    return true;
}

static void Worker(ThreadSafeStack& stack, std::atomic<bool>& finish, 
                   std::mutex& io_mutex) {
    while (true) {
        bool success;
        int value = stack.Pop(success);
        if (!success) {
            if (finish.load()) {
                return;
            } else {
                continue;
            }
        }
        if (IsPrime(value)) {
            std::unique_lock<std::mutex> lock(io_mutex);
            std::cout << value << ' ';
        }
    }
}

void Solver::Run() {
    std::ifstream fin(filename_);

    ThreadSafeStack numbers_stack;
    std::atomic<bool> finish{0};
    std::mutex io_mutex;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < thread_count_; ++i) {
        threads.emplace_back(Worker, std::ref(numbers_stack), 
                             std::ref(finish), std::ref(io_mutex));
    }

    int value;
    while (fin >> value) {
        numbers_stack.Push(value);
    }

    finish.store(true);

    for (auto&& thread : threads) {
        thread.join();
    }
    std::cout << std::endl;
}
