#ifndef _Tree_h
#define _Tree_h

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Node234.h"
#include "Queue234.h"
using namespace std;

class Tree {
	Node* root;

public:
	friend class BinaryTree;

	Tree() {
		root = new Node;
	}

	~Tree() {
		root = nullptr;
	}

	Tree* addAction(int k, char* a);

	void create234Tree(string s);

	char* findAction(int k);

	int countKeys(int k);

	void deallocateTree();

	void PrintSpaces(int n);

	int findHeight();

	void printTree();

	bool deleteAction(int k, char* a);

	void deleteActionWithHighestPriority();

	void changeActionPriority(int k, char *a, int newk);
};
#endif