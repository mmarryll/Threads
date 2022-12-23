#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

template<class T>
class Stack {
public:

	Stack() : head(nullptr) {}

	void Pop(T& value) {
		Node* old_head = head.load();
		while (!head.compare_exchange_weak(old_head, old_head->next));
		value = old_head->value;
	}

	void Push(const T& obj) {
		Node* newnd = new Node(obj);
		newnd->next = head.load();
		while (!head.compare_exchange_weak(newnd->next, newnd));
	}
	
	void Print() {
		Node* temp = head;
		if (head != nullptr) {
			while (temp != nullptr) {
				cout << temp->value << " ";
				temp = temp->next;
			}
			cout << endl;
		}
		cout << endl;
	}

	private:
	struct Node {
		Node* next;
		T value;
		Node(const T& data) : value(data), next(nullptr) {}
	};
	atomic<Node*> head;
};
  
int main() {
	Stack<int> stk;
	int value = 0;
	vector<thread> threads;
	for (int i = 0; i < 1; ++i) {
		threads.emplace_back(&Stack<int>::Push,stk, value);
		value++;
	}
	stk.Print();
	for (int i = 0; i < 1; ++i) {
		threads.emplace_back(&Stack<int>::Pop,stk, value);
		value += value - 2;
	}
	stk.Print();
	for (auto&& thr : threads) {
		thr.join();
	}
}

