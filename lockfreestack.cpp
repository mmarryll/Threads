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

	T Pop(T& value) {
		Node* old_head = head.load(memory_order_relaxed);
		if (old_head == nullptr) {
			return INT_MIN;
		}
		Node* new_head;
		do {
			new_head = old_head->next;
		} while (!head.compare_exchange_weak(old_head, new_head, memory_order_acquire, memory_order_relaxed));

		//value = old_head->data;
		return true;
	}

	void Push(T obj) {
		Node* old_head = head.load(memory_order_relaxed);
		Node* newnd = new Node;
		newnd->value = obj;
		do {
			newnd->next = old_head;
			head = newnd;
		} while (!atomic_compare_exchange_weak(old_head, head, memory_order_acquire, memory_order_relaxed));
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

