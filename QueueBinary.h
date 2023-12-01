#ifndef _QueueBinary_h
#define _QueueBinary_h

#include "BinaryNode.h"
#include <iostream>
using namespace std;

class QueueBinary {
	struct QueueNodeBinary {
		BinaryNode* info;
		QueueNodeBinary* next;

		QueueNodeBinary() {
			info = nullptr;
			next = nullptr;
		}
	};
	QueueNodeBinary* front;
	QueueNodeBinary* rear;

public:
	friend class BinaryTree;
	QueueBinary();

	void ins(BinaryNode* x);

	BinaryNode* del();

	bool queueEmpty();

};

#endif
