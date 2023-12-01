#include "Node234.h"

Node::Node() {
	key[0] = INT_MIN;
	key[1] = key[2] = INT_MAX;
	action[0] = action[1] = action[2] = nullptr;
	child[0] = child[1] = child[2] = child[3] = nullptr;
	num = 0;
	parent = nullptr;
}

Node::~Node() {
	for (int i = 0; i < 3; i++) {
		if (action[i] != nullptr) {
			delete[] action[i];
			action[i] = nullptr;
		}
	}
	child[0] = child[1] = child[2] = child[3] = nullptr;
}

bool Node::isLeaf() {
	for (int i = 0; i < 4; i++) {
		if (child[i] != nullptr) return false;
	}
	return true;
}

Node* Node::addKey(int k, char *a) {
	if (num == 0) {
		key[1] = k;
		action[1] = a;
	}
	if (num == 1) {
		if (k < key[1] || (k == key[1] && strcmp(a, action[1]) < 0)) {
			key[0] = k;
			action[0] = a;
		}
		else { //k > key[1] || (k == key[1] && strcmp(a, action[1]) > 0)
			key[2] = k;
			action[2] = a;
		}
	}
	if (num == 2) {
		if (key[0] == INT_MIN) {
			key[0] = k;
			action[0] = a;
		}
		else { //key3 == INT_MAX
			key[2] = k;
			action[2] = a;
		}
		for (int i = 0; i < 2; i++) {
			for (int j = i; j < 3; j++) {
				if ((key[i] > key[j]) || ((key[i] == key[j]) && (strcmp(action[i], action[j]) > 0))) {
					int p = key[i]; key[i] = key[j];  key[j] = p;
					char *s = action[i]; action[i] = action[j]; action[j] = s;
				}
			}
		}
	}
	if (num != 3) num++;
	return this;
}

Node* Node::removeKey(int k) {
	if (key[0] == k) {
		key[0] = INT_MIN;
		action[0] = nullptr;
		num--;
		return this;
	}
	if (key[2] == k) {
		key[2] = INT_MAX;
		action[2] = nullptr;
		num--;
		return this;
	}
	if (key[1] == k) {
		key[1] = INT_MAX;
		action[1] = nullptr;
		num--;
		return this;
	}
	return this;
}

Node* Node::findRealBrother() {	
	int i;
	for (i = 0; i < 4; i++) {
		if(parent->child[i] == this) break;
	}
	if (parent->key[0] == INT_MIN && parent->key[2] == INT_MAX) {
		if (i == 1) return parent->child[2];
		if (i == 2) return parent->child[1];
	}
	else {
		if (i == 0) return parent->child[1];
		if (i == 1) return parent->child[0];
		if (i == 2) return parent->child[3];
		if (i == 3) return parent->child[2];
	}
}

Node* Node::findNotRealBrother() {
	int i;
	for (i = 0; i < 4; i++) {
		if (parent->child[i] == this) break;
	}
	if (parent->key[0] == INT_MIN) {
		return parent->child[2];
	}
	else { //parent->key[2] == INT_MAX
		return parent->child[1];
	}
}

Node * Node::findSuccessor(int k, char* a, int & sk, char *& sa) {
	int i; Node* p, *q = nullptr;
	for (i = 0; i < 3; i++)
		if (k == key[i] && strcmp(a, action[i]) == 0) break;
	if (i == 3) p = child[i];
	else p = child[i + 1];
	while (p != nullptr) {
		q = p;
		if (p->child[0] != nullptr)  p = p->child[0]; 
		else p = p->child[1]; 
	}
	sk = (q->key[0] != INT_MIN)? q->key[0] : q->key[1];
	sa = (q->key[0] != INT_MIN) ? q->action[0] : q->action[1];
	return q;
}

ostream &operator<<(ostream &os, Node* p) {
	os << "|";
	if (p->key[0] != INT_MIN) os << setw(3) << p->key[0];
	else os << "___";
	os << " ";
	if (p->key[1] != INT_MAX) os << setw(3) << p->key[1];
	else os << "___";
	os << " ";
	if (p->key[2] != INT_MAX) os << setw(3) << p->key[2];
	else os << "___";
	os << "|";
	return os;
}