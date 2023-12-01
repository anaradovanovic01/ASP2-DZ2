#include "Queue234.h"

Queue234::Queue234() {
	QueueNode234* front = nullptr;
	QueueNode234* rear = nullptr;
}

void Queue234::ins(Node* x) {
	QueueNode234* p = new QueueNode234;
	p->info = x;
	p->next = nullptr;
	if (rear == nullptr)
		front = p;
	else
		rear->next = p;
	rear = p;
	return;
}

Node* Queue234::del() {
	QueueNode234* p;
	Node* x;
	if (front == nullptr) {
		cout << "Underflow" << endl;
		exit(1);
	}
	else {
		p = front;
		x = p->info;
		front = p->next;
		if (front == nullptr)
			rear = nullptr;
		delete p;
		return x;
	}
}

bool Queue234::queueEmpty() {
	if (front) return false;
	else return true;
}