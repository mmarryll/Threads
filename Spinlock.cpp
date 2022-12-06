#include <iostream>
#include <vector>
#include <thread>
#include <atomic>
using namespace std;

class Spinlock {
	Spinlock() : lock(false) {}

	void Lock() {
		while (lock.exchange(true));
	}

	void Unlock() {
		lock.store(false);
	}

private:
	atomic<bool> lock;
};
