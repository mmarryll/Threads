#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

mutex mtx;
condition_variable cv;
int prime = 0;

bool IsItPrime(int num) {
	for (int i = 2; i < num / 2; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

void FindNextPrime(int num) {
	unique_lock<mutex> guard(mtx);
	while (!IsItPrime(num)) {
		num++;
	}
    prime = num;
	guard.unlock();
	cv.notify_all();
}

void PrintNextPrime(int num) {
	unique_lock<mutex> guard(mtx);
	while (prime == 0) {
		cv.wait(guard);
	}	
	cout << prime << endl;
}

int main() {
	int num;
	cin >> num;
	thread thr1(FindNextPrime, num);
	thread thr2(PrintNextPrime, num);
	thr1.join();
	thr2.join();
}