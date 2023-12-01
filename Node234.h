#ifndef _Node_h
#define _Node_h

#include <iostream>
#include <cstring>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

class Node {
	int key[3];
	char *action[3];
	Node *child[4], *parent;
	int num;

public:
	friend class Tree;
	friend class BinaryTree;

	Node();

	~Node();

	bool isFull() const {
		if (num == 3) return true;
		else return false;
	}

	bool isEmpty() const{
		if (num == 0) return true;
		else return false;
	}


	bool isLeaf();

	Node* addKey(int k, char *a);

	Node* removeKey(int k);

	Node* findRealBrother();

	Node* findNotRealBrother();

	Node* findSuccessor(int k, char* a, int & sk, char *& sa);

	friend ostream &operator<<(ostream &os, Node* p);

};

#endif
