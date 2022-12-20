#pragma once

#include <vector>
#include <mutex>

class ThreadSafeStack {
public:
    void Push(int value);
    int Pop(bool& success);

private:
    std::vector<int> stack_;
    std::mutex mutex_;
};
