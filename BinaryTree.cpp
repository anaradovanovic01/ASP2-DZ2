#include "BinaryTree.h"

int BinaryTree::findHeight() {
	if (root == nullptr)
		return 0;
	int height = 0, queueSize = 1;
	BinaryNode* p;
	QueueBinary Q = *(new QueueBinary);
	Q.ins(root);
	height = 0;
	while (!Q.queueEmpty()) {
		for (int i = queueSize; i > 0; i--) {
			p = Q.del();
			queueSize--;
			for (int j = 0; j < 4; j++) {
				if (p->left != nullptr) {
					Q.ins(p->left);
					queueSize++;
				}
				if (p->right != nullptr) {
					Q.ins(p->right);
					queueSize++;
				}
			}
		}
		height++;
	}
	return height;
}

void BinaryTree::transformNode(Node* p) {
	BinaryNode *n1, *n2, *n3, *n4;
	if (root == nullptr) {
		n1 = new BinaryNode;
		root = n1;
		n1->black = true;
		n1->key = p->key[1]; n1->action = p->action[1];
		n1->parent = nullptr;
		if (p->key[0] != INT_MIN) {
			n2 = new BinaryNode;
			n2->black = false;
			n2->key = p->key[0];
			n2->action = p->action[0];
			n2->parent = n1;
			n1->left = n2;
			if (p->child[0] != nullptr) {
				n3 = new BinaryNode;
				n3->black = true;
				n3->key = p->child[0]->key[1];
				n3->action = p->child[0]->action[1];
				n3->parent = n2;
				n2->left = n3;
			}
			if (p->child[1] != nullptr) {
				n4 = new BinaryNode;
				n4->black = true;
				n4->key = p->child[1]->key[1];
				n4->action = p->child[1]->action[1];
				n4->parent = n2;
				n2->right = n4;
			}
		}
		else {
			if (p->child[1] != nullptr) {
				n2 = new BinaryNode;
				n2->black = true;
				n2->key = p->child[1]->key[1];
				n2->action = p->child[1]->action[1];
				n2->parent = n1;
				n1->left = n2;
			}
		}
		if (p->key[2] != INT_MAX) {
			n2 = new BinaryNode;
			n2->black = false;
			n2->key = p->key[2];
			n2->action = p->action[2];
			n2->parent = n1;
			n1->right = n2;
			if (p->child[2] != nullptr) {
				n3 = new BinaryNode;
				n3->black = true;
				n3->key = p->child[2]->key[1];
				n3->action = p->child[2]->action[1];
				n3->parent = n2;
				n2->left = n3;
			}
			if (p->child[3] != nullptr) {
				n4 = new BinaryNode;
				n4->black = true;
				n4->key = p->child[3]->key[1];
				n4->action = p->child[3]->action[1];
				n4->parent = n2;
				n2->right = n4;
			}
		}
		else {
			if (p->child[2] != nullptr) {
				n2 = new BinaryNode;
				n2->black = true;
				n2->key = p->child[2]->key[1];
				n2->action = p->child[2]->action[1];
				n2->parent = n1;
				n1->right = n2;
			}
		}
	}
	else {
		n1 = root;
		while (p->key[1] != n1->key || strcmp(p->action[1], n1->action) != 0) {
			if ((p->key[1] < n1->key) || (p->key[1] == n1->key && strcmp(p->action[1], n1->action) < 0)) n1 = n1->left;
			else n1 = n1->right;
		}
		if (p->key[0] != INT_MIN) {
			n2 = new BinaryNode;
			n2->black = false;
			n2->key = p->key[0];
			n2->action = p->action[0];
			n2->parent = n1;
			n1->left = n2;
			if (p->child[0] != nullptr) {
				n3 = new BinaryNode;
				n3->black = true;
				n3->key = p->child[0]->key[1];
				n3->action = p->child[0]->action[1];
				n3->parent = n2;
				n2->left = n3;
			}
			if (p->child[1] != nullptr) {
				n4 = new BinaryNode;
				n4->black = true;
				n4->key = p->child[1]->key[1];
				n4->action = p->child[1]->action[1];
				n4->parent = n2;
				n2->right = n4;
			}
		}
		else {
			if (p->child[1] != nullptr) {
				n2 = new BinaryNode;
				n2->black = true;
				n2->key = p->child[1]->key[1];
				n2->action = p->child[1]->action[1];
				n2->parent = n1;
				n1->left = n2;
			}
		}
		if (p->key[2] != INT_MAX) {
			n2 = new BinaryNode;
			n2->black = false;
			n2->key = p->key[2];
			n2->action = p->action[2];
			n2->parent = n1;
			n1->right = n2;
			if (p->child[2] != nullptr) {
				n3 = new BinaryNode;
				n3->black = true;
				n3->key = p->child[2]->key[1];
				n3->action = p->child[2]->action[1];
				n3->parent = n2;
				n2->left = n3;
			}
			if (p->child[3] != nullptr) {
				n4 = new BinaryNode;
				n4->black = true;
				n4->key = p->child[3]->key[1];
				n4->action = p->child[3]->action[1];
				n4->parent = n2;
				n2->right = n4;
			}
		}
		else {
			if (p->child[2] != nullptr) {
				n2 = new BinaryNode;
				n2->black = true;
				n2->key = p->child[2]->key[1];
				n2->action = p->child[2]->action[1];
				n2->parent = n1;
				n1->right = n2;
			}
		}
	}
}

BinaryTree* BinaryTree::createBinaryTree(Tree t) {
	Node* p = t.root;
	Queue234 Q = *(new Queue234);
	Q.ins(p);
	while (!(Q.queueEmpty())) {
		p = Q.del();
		this->transformNode(p);
		for (int i = 0; i < 4; i++) {
			if (p->child[i] != nullptr)
				Q.ins(p->child[i]);
		}
	}
	return this;
}

void BinaryTree::PrintSpaces(int n) {
	for (int i = 0; i < n; i++)
		cout << " ";
	return;
}

void BinaryTree::printBinaryTree() {
	if (root == nullptr) {
		return;
	}
	int height, level, nextLevelFlag, max;
	height = this->findHeight();
	max = 3 * pow(2, (height - 1)) + pow(2, (height - 1)) - 1;
	BinaryNode *p, *q;
	QueueBinary Q = *(new QueueBinary);
	Q.ins(root);
	Q.ins(nullptr);
	level = 0; nextLevelFlag = 0;
	while (level < height) {
		p = Q.del();
		if (p == nullptr) {
			level++;
			nextLevelFlag = 0;
			cout << endl;
			if (!Q.queueEmpty())
				Q.ins(nullptr);
			continue;
		}
		else {
			if (nextLevelFlag == 0) {
				PrintSpaces((max - (3 * pow(2, level))) / (2 * (pow(2, level) + 1) - 2));
			}
			else
				PrintSpaces(2 * (max - (3 * pow(2, level))) / (2 * (pow(2, level) + 1) - 2) + 1);
			nextLevelFlag = 1;
			if (p->key >= 0)  cout << setw(3) << p->key;
			else cout << " _ ";
		}
		if (p->left != nullptr)
			Q.ins(p->left);
		else {
			q = new BinaryNode;
			q->key = -1;
			Q.ins(q);
		}
		if (p->right != nullptr)
			Q.ins(p->right);
		else {
			q = new BinaryNode;
			q->key = -1;
			Q.ins(q);
		}
	}
	while (!Q.queueEmpty()) Q.del();
	return;
}

