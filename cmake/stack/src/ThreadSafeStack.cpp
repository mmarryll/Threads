#include "ThreadSafeStack.h"

void ThreadSafeStack::Push(int value) {
    std::unique_lock<std::mutex> lock(mutex_);
    stack_.push_back(value);
}

int ThreadSafeStack::Pop(bool& success) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (stack_.empty()) {
        success = false;
        return 0;
    }
    success = true;
    int top = stack_.back();
    stack_.pop_back();
    return top;
}
