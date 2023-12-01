#include "QueueBinary.h"

QueueBinary::QueueBinary() {
	QueueNodeBinary* front = nullptr;
	QueueNodeBinary* rear = nullptr;
}

void QueueBinary::ins(BinaryNode* x) {
	QueueNodeBinary* p = new QueueNodeBinary;
	p->info = x;
	p->next = nullptr;
	if (rear == nullptr)
		front = p;
	else
		rear->next = p;
	rear = p;
	return;
}

BinaryNode* QueueBinary::del() {
	QueueNodeBinary* p;
	BinaryNode* x;
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

bool QueueBinary::queueEmpty() {
	if (front) return false;
	else return true;
}