#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
using namespace std;

mutex mut;
int j = 0;


bool IsItPrime(int num) {
	if (num == 0 || num == 1) return false;
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) return false;
	}
	return true;
}

void Solution(vector<int>& vec, vector<bool>& solution) {
	while (true) {
		unique_lock<mutex> guard(mut);
		if (j == vec.size()) return;
		else j++;
		guard.unlock();
		if (IsItPrime(vec[j - 1])) solution[j - 1] = true;
	}
}

int main() {
	cout << "Enter size: ";
	int size;
	cin >> size;
	vector<int> vec(size);
	srand(time(0));
	for (int i = 0; i < size; i++) {
		vec[i] = rand() % 100;
		cout << vec[i] << " ";
	}
	cout << endl;
	cout << "Enter number of threads: ";
	int numthr;
	cin >> numthr;
	vector <bool> solution(size);
	vector<thread> thr;
	for (int i = 0; i < numthr; i++) {
		thr.emplace_back([&vec, &solution]() {Solution(vec, solution);});
	}
	for (int i = 0; i < thr.size(); i++) {
		thr[i].join();
	}
	cout << endl;
	for (int i = 0; i < size; i++) {
		cout << solution[i] << " ";
	}
}
