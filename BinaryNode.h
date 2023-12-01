#ifndef _BinaryNode_h
#define _BinaryNode_h

class BinaryNode {
	int key;
	char* action;
	bool black;
	BinaryNode *left, *right, *parent;

public:
	friend class BinaryTree;

	BinaryNode();

	~BinaryNode();

};

#endif