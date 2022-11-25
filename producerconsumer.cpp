#include <iostream>
#include <condition_variable>
#include <thread>
#include <mutex>
using namespace std;

mutex mut;
condition_variable cv;
bool flag = false;
int nxtnum = 0;

bool IsItPrime(int num) {
	for (int i = 2; i < num / 2; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

void NextPrime(int num) {
	unique_lock<mutex> guard(mut);
	while (true) {
		if (IsItPrime(num)) break;
		num++;
	}
	nxtnum = num;
	flag = true;
	guard.unlock();
	cv.notify_all();
}

void PrintNextPrime() {
	unique_lock<mutex> guard(mut);
	while (flag == false) {
		cv.wait(guard);
	}
	cout << nxtnum;
}

int main() {
	int num;
	cout << "Enter your num: ";
	cin >> num;
	cout << "Next prime is ";
	thread thr1(NextPrime, num);
	thread thr2(PrintNextPrime);
	thr1.join();
	thr2.join();
}