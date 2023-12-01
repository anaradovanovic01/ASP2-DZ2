#ifndef _BinaryTree_h
#define _BinaryTree_h

#include "BinaryNode.h"
#include "QueueBinary.h"
#include "Tree234.h"
#include "Node234.h"

class BinaryTree {
	BinaryNode* root;

public:

	BinaryTree() {
		root = nullptr;
	}

	~BinaryTree() {
		root = nullptr;
	}

	int findHeight();

	void transformNode(Node* p);

	BinaryTree* createBinaryTree(Tree t);

	void PrintSpaces(int n);

	void printBinaryTree();

};
#endif