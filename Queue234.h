#ifndef _Queue234_h
#define _Queue234_h

#include "Node234.h"

class Queue234 {
	struct QueueNode234 {
		Node* info;
		QueueNode234* next;

		QueueNode234 () {
			info = nullptr;
			next = nullptr;
		}
	};
	QueueNode234* front;
	QueueNode234* rear;

public:
	friend class Tree;
	Queue234();

	void ins(Node* x);

	Node* del();

	bool queueEmpty();

};

#endif