#include "Tree234.h"
#include "Node234.h"

char* Tree::findAction(int k) {
	Node* p = root;
	int i = 0;
	while (p != nullptr) {
		while (i < 3 && k > p->key[i]) i++;
		if (p->key[i] == k) return p->action[i];
		else p = p->child[i];
	}
	cout << "Neuspesna pretraga." << endl;
	return nullptr;
}

Tree* Tree::addAction(int k, char* a) {
	Node *p = root, *q = nullptr, *newNode = nullptr, *oldNewNode = nullptr;
	int midk = INT_MIN; char* mida = nullptr;
	while (p != nullptr) { 
		if (k < p->key[0] || (k == p->key[0] && strcmp(a, p->action[0]) < 0)) { q = p; p = p->child[0]; }
		else {
			if (k < p->key[1] || (k == p->key[1] && strcmp(a, p->action[1]) < 0)) { q = p; p = p->child[1]; }
			else {
				if (k < p->key[2] || (k == p->key[2] && strcmp(a, p->action[2]) < 0)) { q = p; p = p->child[2]; }
				else { q = p; p = p->child[3]; }
			}
		}
	}
	p = q;
	int l = 1;
	while (l) {
		if (p->isFull()) { 
			midk = p->key[1]; mida = p->action[1]; 
			Node *newNode = new Node; 
			newNode->key[1] = p->key[0]; newNode->action[1] = p->action[0]; newNode->num = 1;
			p->removeKey(p->key[0]); 
			p->num = 1;
			newNode->child[1] = p->child[0];
			if (p->child[0]) p->child[0]->parent = newNode;
			p->child[0] = nullptr; 
			newNode->child[2] = p->child[1];
			if (p->child[1]) p->child[1]->parent = newNode;
			p->child[1] = p->child[2]; 
			p->child[2] = p->child[3];
			p->child[3] = nullptr;
			p->key[1] = p->key[2]; p->key[2] = INT_MAX; 
			p->action[1] = p->action[2]; p->action[2] = nullptr;
			if (k < midk) {
				newNode->addKey(k, a);
				if (k < newNode->key[1]) newNode->child[0] = oldNewNode; 
				else { newNode->child[3] = newNode->child[2]; newNode->child[2] = oldNewNode; }
				if(oldNewNode) oldNewNode->parent = newNode;
			}
			else {
				p->addKey(k, a);
				if (k < p->key[1]) p->child[0] = oldNewNode;
				else { p->child[3] = p->child[2]; p->child[2] = oldNewNode; }
				if(oldNewNode) oldNewNode->parent = p;
			}
			k = midk; a = mida; oldNewNode = newNode; 
			if (p == root) { 
				root = new Node;
				root->addKey(k, a);
				root->child[1] = oldNewNode;
				root->child[2] = p;
				oldNewNode->parent = root;
				p->parent = root;
				l = 0;
				break;
			}
			else p = p->parent;
			l = 1;
		}
		else { 
			if (oldNewNode) { 
				oldNewNode->parent = p;
				if (p->num == 1) { 
					if (k < p->key[1]) p->child[0] = oldNewNode;
					else { p->child[3] = p->child[2]; p->child[2] = oldNewNode; }
				}
				if (p->num == 2) {
					if (p->key[0] == INT_MIN) p->child[0] = oldNewNode;
					else  p->child[3] = oldNewNode;
					for (int i = 0; i < 3; i++) {
						for (int j = i; j < 4; j++) {
							if (p->child[i]->key[1] > p->child[j]->key[1]) {
								Node* t = p->child[i]; p->child[i] = p->child[j];  p->child[j] = t;
							}
						}
					}
				}
			}
			p->addKey(k, a); 
			l = 0;
		}
	}
	return this;
}

void Tree::create234Tree(string name) {
	ifstream dat;
	dat.open(name);
	if (!dat.is_open()) {
		cout << "Problem pri otvaranju datoteke" << endl;
		exit(1);
	}
	char *a, c;
	int i, k;
	while (dat >> noskipws >> c) {
		a = new char[256]; i = 0;
		while (c) {
			a[i++] = c;
			dat >> noskipws >> c;
			if (c == '|') break;
		}
		a[i] = '\0';
		dat >> k;
		dat >> noskipws >> c;
		this->addAction(k, a);
	}
	dat.close();
	return;
}

int Tree::countKeys(int k) {
	int cnt = 0;
	Node* p = root;
	Queue234 Q = *(new Queue234);
	Q.ins(p);
	while (!(Q.queueEmpty())) {
		p = Q.del();
		for (int i = 0; i < 3; i++) {
			if (p->key[i] == k) cnt++;
		}
		for (int i = 0; i < 4; i++) {
			if (p->child[i] != nullptr) 
				Q.ins(p->child[i]);
		}
	}
	return cnt;
}

void Tree:: deallocateTree() {
	if (root == nullptr) return;
	Node* p = root;
	Queue234 Q = *(new Queue234);
	Q.ins(p);
	while (!(Q.queueEmpty())) {
		p = Q.del();
		for (int i = 0; i < 4; i++) {
			if (p->child[i] != nullptr)
				Q.ins(p->child[i]);
		}
		delete p;
	}
	return;
}

int Tree::findHeight() {
	if (root == nullptr)
		return 0;
	int height = 1;
	Node* p = root;
	while (!p->isLeaf()) {
		height++;
		if (p->child[1] != nullptr) p = p->child[1];
		else p = p->child[2];
	}
	return height;
}

void Tree::PrintSpaces(int n) {
	for (int i = 0; i < n; i++)
		cout << " ";
	return;
}

void Tree::printTree() {
	if (root == nullptr) {
		cout << "|___ ___ ___|" << endl;
		return;
	}
	int height = this->findHeight();
	int max = 13 * pow(4, (height - 1)) + pow(4, (height - 1)) - 1;
	int level = 0;
	Node* p, *q, *pa;
	Queue234 Q = *(new Queue234);
	Queue234 Qa = *(new Queue234);
	Q.ins(root); Qa.ins(root);
	Q.ins(nullptr); Qa.ins(nullptr);
	int nextLevelFlag = 0, nextLevelFlagAction;
	while (level < height) {
		p = Q.del();
		if (p == nullptr) {
			pa = Qa.del();
			nextLevelFlagAction = 0;
			cout << endl;
			while (pa != nullptr) {
				if (nextLevelFlagAction == 0) {
					PrintSpaces((max - (13 * pow(4, level))) / (2 * (pow(4, level) + 1) - 2));
				}
				else
					PrintSpaces(2 * (max - (13 * pow(4, level))) / (2 * (pow(4, level) + 1) - 2) + 1);
				nextLevelFlagAction = 1;
				cout << " ";
				if (pa->key[0] != INT_MIN) cout << pa->action[0][0] << pa->action[0][1] << pa->action[0][2];
				else cout << "   ";
				cout << " ";
				if (pa->key[1] != INT_MAX) cout << pa->action[1][0] << pa->action[1][1] << pa->action[1][2];
				else cout << "   ";
				cout << " ";
				if (pa->key[2] != INT_MAX) cout << pa->action[2][0] << pa->action[2][1] << pa->action[2][2];
				else cout << "   ";
				cout << " ";
				pa = Qa.del();
			}
			level++;
			nextLevelFlag = 0;
			cout << endl << endl;
			if (!Q.queueEmpty()) {
				Q.ins(nullptr); Qa.ins(nullptr);
			}
			continue;
		}
		else {
			if (nextLevelFlag == 0) {
				PrintSpaces((max - (13 * pow(4, level))) / (2 * (pow(4, level) + 1) - 2));
			}
			else
				PrintSpaces(2* (max - (13 * pow(4, level))) / (2 * (pow(4, level) + 1) - 2) +1);
			nextLevelFlag = 1;
			cout << p;
		}
		for (int i = 0; i < 4; i++) {
			if (p->child[i] != nullptr) { Q.ins(p->child[i]); Qa.ins(p->child[i]); }
			else {
				q = new Node; 
				Q.ins(q); Qa.ins(q);
			}
		}
	}
	while (!Q.queueEmpty()) Q.del();
	while (!Qa.queueEmpty()) Qa.del();
	return;
}

bool Tree::deleteAction(int k, char* a) {
	if (root == nullptr) return false;
	Node *p = root, *q = nullptr, *s, *newNode = nullptr, *oldNewNode = nullptr, *bro, *nephew; int n = -1, l = 1;
	while (p != nullptr) {
		for (int i = 0; i < 3; i++) {
			if (p->key[i] == k && strcmp(p->action[i], a) == 0) { l = 0; q = p; p = nullptr; break; }
		}
		if (l) {
			if (k < p->key[0] || (k == p->key[0] && strcmp(a, p->action[0]) < 0)) { q = p; p = p->child[0]; }
			else {
				if (k < p->key[1] || (k == p->key[1] && strcmp(a, p->action[1]) < 0)) { q = p; p = p->child[1]; }
				else {
					if (k < p->key[2] || (k == p->key[2] && strcmp(a, p->action[2]) < 0)) { q = p; p = p->child[2]; }
					else { q = p; p = p->child[3]; }
				}
			}
		}
	}
	p = q;
	q = q->parent;
	for (int i = 0; i < 3; i++) {
		if (k == p->key[i] && strcmp(a, p->action[i]) == 0) n = i;
	}
	if (n < 0) return false;
	if (!p->isLeaf()) { //ako je unutrasnji cvor, zameni sa sledbenikom
		int pom, ns; char* pom2;
		s = p->findSuccessor(k, a, pom, pom2);
		for (int i = 0; i < 3; i++) {
			if (pom == s->key[i] && pom2 == s->action[i]) ns = i;
		}
		s->key[ns] = p->key[n];
		s->action[ns] = p->action[n];
		p->key[n] = pom;
		p->action[n] = pom2;
		p = s;
		q = p->parent;
		n = ns;
	}
	if (n == 0 || n == 2) { //ako se brise crveni iz lista
		p->key[n] = (n == 0) ? INT_MIN : INT_MAX;
		delete[] p->action[n];
		p->action[n] = nullptr;
		p->num--;
	}
	else { //brise se crni iz lista
		if (p->num > 1) { //ima dovoljno
			int pom;
			if (p->key[2] != INT_MAX) pom = 2;
			else pom = 0;
			p->key[1] = p->key[pom];
			delete[] p->action[1];
			p->action[1] = p->action[pom];
			p->key[pom] = (pom == 0) ? INT_MIN : INT_MAX;
			p->action[pom] = nullptr;
			p->num--;
		}
		else { //nema dovoljno
			while (true) {
				if (p == root && oldNewNode == nullptr) {
					delete p;
					root = nullptr;
					break;
				}
				bro = p->findRealBrother();
				if (bro != nullptr) { //ima brata
					if (bro->isFull()) { //moze pozajmica, pun brat
						int nf;
						for (nf = 0; nf < 4; nf++) {
							if (q->child[nf] == p) break;
						}
						if (q->num == 1) { //otac ima jedan kljuc
							if (nf == 1) { //p < bro
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[1] = q->key[1]; p->action[1] = q->action[1];
								q->key[1] = bro->key[1]; q->action[1] = bro->action[1];
								p->key[2] = bro->key[0]; p->action[2] = bro->action[0];
								bro->key[0] = INT_MIN; bro->action[0] = nullptr;
								p->child[2] = bro->child[0]; bro->child[0]->parent = p; bro->child[0] = nullptr;
								p->child[3] = bro->child[1]; bro->child[1]->parent = p;
								bro->child[1] = bro->child[2];
								bro->child[2] = bro->child[3]; bro->child[3] = nullptr;
								bro->key[1] = bro->key[2]; bro->key[2] = INT_MAX;
								bro->action[1] = bro->action[2]; bro->action[2] = nullptr;
								if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
							}
							else { //bro < p
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[1] = q->key[1]; p->action[1] = q->action[1];
								q->key[1] = bro->key[1]; q->action[1] = bro->action[1];
								p->key[0] = bro->key[2]; p->action[0] = bro->action[0];
								bro->key[2] = INT_MAX; bro->action[2] = nullptr;
								p->child[0] = bro->child[2]; bro->child[2]->parent = p;
								p->child[1] = bro->child[3]; bro->child[3]->parent = p; bro->child[3] = nullptr;
								bro->child[2] = bro->child[1];
								bro->child[1] = bro->child[0]; bro->child[0] = nullptr;
								bro->key[1] = bro->key[0]; bro->key[0] = INT_MIN;
								bro->action[1] = bro->action[0]; bro->action[0] = nullptr;
								if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
							}
						}
						else { //otac je pun
							int np, nb;
							np = (nf == 0 || nf == 2) ? 2 : 0;
							nb = (nf == 0 || nf == 2) ? 0 : 2;
							nf = (nf == 0 || nf == 1) ? 0 : 2;
							if (oldNewNode) p->action[1] = nullptr;
							else delete[] p->action[1];
							p->key[1] = q->key[nf];	p->action[1] = q->action[nf];
							q->key[nf] = bro->key[1]; q->action[nf] = bro->action[1];
							p->key[np] = bro->key[nb]; p->action[np] = bro->action[nb];
							p->child[np] = bro->child[nb]; bro->child[nb]->parent = p; 
							p->child[np + 1] = bro->child[nb + 1]; bro->child[nb + 1]->parent = p;
							bro->key[nb] = (nb == 0) ? INT_MIN : INT_MAX; bro->action[nb] = nullptr;
							bro->key[1] = bro->key[np]; bro->action[1] = bro->action[np];
							Node* pom = (nb == 0) ? bro->child[2] : bro->child[0];
							bro->child[2] = (nb == 0) ? bro->child[3] : bro->child[1]; bro->child[1] = pom;
							bro->key[np] = (np == 0) ? INT_MIN : INT_MAX; bro->action[np] = nullptr;
							bro->child[0] = nullptr; bro->child[3] = nullptr;
							if (oldNewNode) {
								if (oldNewNode->key[1] < p->key[0] || (oldNewNode->key[1] == p->key[0] && strcmp(oldNewNode->action[1], p->action[0]) < 0)) p->child[0] = oldNewNode;
								else {
									if (oldNewNode->key[1] < p->key[1] || (oldNewNode->key[1] == p->key[1] && strcmp(oldNewNode->action[1], p->action[1]) < 0)) p->child[1] = oldNewNode;
									else {
										if (oldNewNode->key[1] < p->key[2] || (oldNewNode->key[1] == p->key[2] && strcmp(oldNewNode->action[1], p->action[2]) < 0)) p->child[2] = oldNewNode;
										else p->child[0] = oldNewNode;
									}
								}
								oldNewNode->parent = p;
							}
						}
						bro->num = 1; p->num = 2;
						break;
					}
					if (bro->num == 2) { //moze pozajmica, brat nije pun
						if (q->num == 1) { //otac ima jednan kljuc
							int nf;
							for (nf = 0; nf < 4; nf++) {
								if (q->child[nf] == p) break;
							}
							if (nf == 1) { //p < bro
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[1] = q->key[1]; p->action[1] = q->action[1];
								if (bro->key[0] == INT_MIN) { //bro -> |_ 10 20|
									q->key[1] = bro->key[1]; q->action[1] = bro->action[1];
									bro->key[1] = bro->key[2]; bro->key[2] = INT_MAX;
									bro->action[1] = bro->action[2]; bro->action[2] = nullptr;
									p->child[2] = bro->child[1]; bro->child[1]->parent = p;
									bro->child[1] = bro->child[2];
									bro->child[2] = bro->child[3];
									bro->child[3] = nullptr;
									if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
								}
								else { //bro -> |_ 10 20|
									q->key[1] = bro->key[0]; bro->key[0] = INT_MIN;
									q->action[1] = bro->action[0]; bro->action[0] = nullptr;
									p->child[2] = bro->child[0]; bro->child[0]->parent = p; bro->child[0] = nullptr;
									if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
								}
							}
							else { //bro < p
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[1] = q->key[1]; p->action[1] = q->action[1];
								if (bro->key[0] == INT_MIN) { //bro -> |_ 10 20|
									q->key[1] = bro->key[2]; bro->key[2] = INT_MAX;
									q->action[1] = bro->action[2]; bro->action[2] = nullptr;
									p->child[1] = bro->child[3]; bro->child[3]->parent = p; bro->child[3] = nullptr;
									if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
								}
								else { //bro -> |_ 10 20|
									q->key[1] = bro->key[1]; q->action[1] = bro->action[1];
									bro->key[1] = bro->key[0]; bro->key[0] = INT_MIN;
									bro->action[1] = bro->action[0]; bro->action[0] = nullptr;
									p->child[1] = bro->child[2]; bro->child[2]->parent = p;
									bro->child[2] = bro->child[1];
									bro->child[1] = bro->child[0];
									bro->child[0] = nullptr;
									if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
								}
							}
						}
						else { //otac je pun
							int nf;
							for (nf = 0; nf < 4; nf++) {
								if (q->child[nf] == p) break;
							}
							if (nf == 0 || nf == 2) { //p < bro
								nf = (nf == 0 || nf == 1) ? 0 : 2;
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[1] = q->key[nf]; p->action[1] = q->action[nf];
								if (bro->key[0] == INT_MIN) { //_ 5 10
									q->key[nf] = bro->key[1]; q->action[nf] = bro->action[1];
									bro->key[1] = bro->key[2]; bro->action[1] = bro->action[2];
									bro->key[2] = INT_MAX; bro->action[2] = nullptr;
									p->child[2] = bro->child[1]; bro->child[1]->parent = p;
									bro->child[1] = bro->child[2]; bro->child[2] = bro->child[3]; bro->child[3] = nullptr;
									if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
								}
								else { // 5 10 _
									q->key[nf] = bro->key[0]; q->action[nf] = bro->action[0];
									bro->key[0] = INT_MIN; bro->action[0] = nullptr;
									p->child[2] = bro->child[0]; bro->child[0]->parent = p; bro->child[0] = nullptr;
									if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
								}
							}
							else { // bro < p
								nf = (nf == 0 || nf == 1) ? 0 : 2;
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[1] = q->key[nf]; p->action[1] = q->action[nf];
								if (bro->key[0] == INT_MIN) { //_ 5 10
									q->key[nf] = bro->key[2]; q->action[nf] = bro->action[2];
									bro->key[2] = INT_MAX; bro->action[2] = nullptr;
									p->child[1] = bro->child[3]; bro->child[3]->parent = p; bro->child[3] = nullptr;
									if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
								}
								else { // 5 10 _
									q->key[nf] = bro->key[1]; q->action[nf] = bro->action[1];
									bro->key[1] = bro->key[0]; bro->action[1] = bro->action[0];
									bro->key[0] = INT_MIN; bro->action[0] = nullptr;
									p->child[1] = bro->child[1];  bro->child[1]->parent = p;
									bro->child[2] = bro->child[1]; bro->child[1] = bro->child[0]; bro->child[0] = nullptr;
									if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
								}
							}
						}
						bro->num = 1;
						break;
					}
					if (bro->num == 1) { //ne moze pozajmica
						if (q->num > 1) { //otac ima dovoljno
							int nf;
							for (nf = 0; nf < 4; nf++) {
								if (q->child[nf] == p) break;
							}
							switch (nf) {
							case 0: { //p < bro, otac je levi
								if (oldNewNode) p->action[1] = nullptr;
								delete p; q->child[0] = nullptr;
								bro->key[2] = bro->key[1]; bro->action[2] = bro->action[1];
								bro->child[3] = bro->child[2]; bro->child[2] = bro->child[1];
								bro->key[1] = q->key[0]; bro->action[1] = q->action[0];
								q->key[0] = INT_MIN; q->action[0] = nullptr;
								if (oldNewNode) { bro->child[1] = oldNewNode; oldNewNode->parent = bro; }
								break;
							}
							case 1: { //bro < p, otac je levi
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[0] = bro->key[1]; p->action[0] = bro->action[1];
								p->child[0] = bro->child[1]; bro->child[1]->parent = p; bro->child[1] = nullptr;
								p->child[1] = bro->child[2]; bro->child[2]->parent = p; bro->child[2] = nullptr;
								p->key[1] = q->key[0]; p->action[1] = q->action[0];
								q->key[0] = INT_MIN; q->action[0] = nullptr;
								if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
								bro->action[1] = nullptr; delete bro; q->child[0] = nullptr;
								break;
							}
							case 2: { //p < bro, otac je desni
								if (oldNewNode) p->action[1] = nullptr;
								else delete[] p->action[1];
								p->key[2] = bro->key[1]; p->action[2] = bro->action[1];
								p->child[3] = bro->child[2]; bro->child[2]->parent = p; bro->child[2] = nullptr;
								p->child[2] = bro->child[1]; bro->child[1]->parent = p; bro->child[1] = nullptr;
								p->key[1] = q->key[2]; p->action[1] = q->action[2];
								q->key[2] = INT_MAX; q->action[2] = nullptr;
								if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
								bro->action[1] = nullptr; delete bro; q->child[3] = nullptr;
								break;
							}
							case 3: { //bro < p, otac je desni
								if (oldNewNode) p->action[1] = nullptr;
								delete p; q->child[3] = nullptr;
								bro->key[0] = bro->key[1]; bro->action[0] = bro->action[1];
								bro->child[0] = bro->child[1]; bro->child[1] = bro->child[2];
								bro->key[1] = q->key[2]; bro->action[1] = q->action[2];
								q->key[2] = INT_MAX; q->action[2] = nullptr;
								if (oldNewNode) { bro->child[2] = oldNewNode; oldNewNode->parent = bro; }
								break;
							}
							}
							q->num--; bro->num++;
							break;
						}
						else { //otac nema dovoljno
							if (oldNewNode) p->action[1] = nullptr; 
							delete p;
							if (p == q->child[1]) { //p < bro
								q->child[1] = nullptr;
								bro->key[2] = bro->key[1];
								bro->action[2] = bro->action[1];
								bro->key[1] = q->key[1];
								bro->num = 2;
								bro->action[1] = q->action[1];
								bro->child[3] = bro->child[2];
								bro->child[2] = bro->child[1];
								bro->child[1] = nullptr;
								q->child[2] = nullptr;
							}
							else { //bro < p
								q->child[2] = nullptr;
								bro->key[0] = bro->key[1];
								bro->action[0] = bro->action[1];
								bro->key[1] = q->key[1];
								bro->num = 2;
								bro->action[1] = q->action[1];
								bro->child[0] = bro->child[1];
								bro->child[1] = bro->child[2];
								bro->child[2] = nullptr;
								q->child[1] = nullptr;
							}
							newNode = bro;
							if (oldNewNode) {
								if (oldNewNode->key[1] < newNode->key[0] || (oldNewNode->key[1] == newNode->key[0] && strcmp(oldNewNode->action[1], newNode->action[0]) < 0)) newNode->child[0] = oldNewNode;
								else {
									if (oldNewNode->key[1] < newNode->key[1] || (oldNewNode->key[1] == newNode->key[1] && strcmp(oldNewNode->action[1], newNode->action[1]) < 0)) newNode->child[1] = oldNewNode;
									else {
										if (oldNewNode->key[1] < newNode->key[2] || (oldNewNode->key[1] == newNode->key[2] && strcmp(oldNewNode->action[1], newNode->action[2]) < 0)) newNode->child[2] = oldNewNode;
										else newNode->child[0] = oldNewNode;
									}
								}
							}
							oldNewNode = newNode;
							p = q;  q = q->parent;
							if (p == root) {
								root = oldNewNode;
								if (oldNewNode) p->action[1] = nullptr;
								delete p;
								break;
							}
						}
					}
				}
				else { //nema brata
					nephew = p->findNotRealBrother();
					if (nephew->isFull()) { //moze pozajmica, pun bratanac
						if (q->key[0] == INT_MIN) { //p < nephew
							if (oldNewNode) p->action[1] = nullptr;
							else delete[] p->action[1];
							for (int i = 0; i < 2; i++) { q->key[i] = q->key[i + 1]; q->action[i] = q->action[i + 1]; }
							for (int i = 0; i < 3; i++) q->child[i] = q->child[i + 1];
							q->key[2] = INT_MAX; q->action[2] = nullptr; q->child[3] = nullptr;
							p->key[1] = q->key[0]; p->action[1] = q->action[0];
							p->key[2] = nephew->key[0]; p->action[2] = nephew->action[0];
							nephew->key[0] = INT_MIN; nephew->action[0] = nullptr;
							q->key[0] = nephew->key[1]; q->action[0] = nephew->action[1];
							nephew->key[1] = nephew->key[2]; nephew->action[1] = nephew->action[2];
							nephew->key[2] = INT_MAX; nephew->action[2] = nullptr;
							p->child[2] = nephew->child[0]; nephew->child[0]->parent = p; 
							p->child[3] = nephew->child[1]; nephew->child[1]->parent = p;
							nephew->child[1] = nephew->child[2]; nephew->child[2] = nephew->child[3];
							nephew->child[0] = nullptr; nephew->child[3] = nullptr;
							if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
						}
						else { // nephew < p
							if (oldNewNode) p->action[1] = nullptr;
							else delete[] p->action[1];
							for (int i = 2; i > 0; i--) { q->key[i] = q->key[i - 1]; q->action[i] = q->action[i - 1]; }
							for (int i = 3; i > 0; i--) q->child[i] = q->child[i - 1];
							q->key[0] = INT_MIN; q->action[0] = nullptr; q->child[0] = nullptr;
							p->key[1] = q->key[2]; p->action[1] = q->action[2];
							p->key[0] = nephew->key[2]; p->action[0] = nephew->action[2];
							nephew->key[2] = INT_MAX; nephew->action[2] = nullptr;
							q->key[2] = nephew->key[1]; q->action[2] = nephew->action[1];
							nephew->key[1] = nephew->key[0]; nephew->action[1] = nephew->action[0];
							nephew->key[0] = INT_MIN; nephew->action[1] = nullptr;
							p->child[0] = nephew->child[2]; nephew->child[2]->parent = p;
							p->child[1] = nephew->child[3]; nephew->child[3]->parent = p;
							nephew->child[2] = nephew->child[1]; nephew->child[1] = nephew->child[0];
							nephew->child[0] = nullptr; nephew->child[3] = nullptr;
							if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
						}
						nephew->num = 1; p->num = 2;
						break;
					}
					if (nephew->num == 2) {//moze pozajmica, bratanac nije pun
						if (q->key[0] == INT_MIN) { //p < nephew
							for (int i = 0; i < 2; i++) { q->key[i] = q->key[i + 1]; q->action[i] = q->action[i + 1]; }
							for (int i = 0; i < 3; i++) q->child[i] = q->child[i + 1];
							q->key[2] = INT_MAX; q->action[2] = nullptr; q->child[3] = nullptr;
						}
						else { // nephew < p
							for (int i = 2; i > 0; i--) { q->key[i] = q->key[i - 1]; q->action[i] = q->action[i - 1]; }
							for (int i = 3; i > 0; i--) q->child[i] = q->child[i - 1];
							q->key[0] = INT_MIN; q->action[0] = nullptr; q->child[0] = nullptr;
						}
						int nf;
						for (nf = 0; nf < 4; nf++) {
							if (q->child[nf] == p) break;
						}
						bro = nephew;
						if (nf == 0 || nf == 2) { //p < bro
							nf = (nf == 0 || nf == 1) ? 0 : 2;
							if (oldNewNode) p->action[1] = nullptr;
							else delete[] p->action[1];
							p->key[1] = q->key[nf]; p->action[1] = q->action[nf];
							if (bro->key[0] == INT_MIN) { //_ 5 10
								q->key[nf] = bro->key[1]; q->action[nf] = bro->action[1];
								bro->key[1] = bro->key[2]; bro->action[1] = bro->action[2];
								bro->key[2] = INT_MAX; bro->action[2] = nullptr;
								p->child[2] = bro->child[1]; bro->child[1]->parent = p;
								bro->child[1] = bro->child[2]; bro->child[2] = bro->child[3]; bro->child[3] = nullptr;
								if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
							}
							else { // 5 10 _
								q->key[nf] = bro->key[0]; q->action[nf] = bro->action[0];
								bro->key[0] = INT_MIN; bro->action[0] = nullptr;
								p->child[2] = bro->child[0]; bro->child[0]->parent = p; bro->child[0] = nullptr;
								if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
							}
						}
						else { // bro < p
							nf = (nf == 0 || nf == 1) ? 0 : 2;
							if (oldNewNode) p->action[1] = nullptr;
							else delete[] p->action[1];
							p->key[1] = q->key[nf]; p->action[1] = q->action[nf];
							if (bro->key[0] == INT_MIN) { //_ 5 10
								q->key[nf] = bro->key[2]; q->action[nf] = bro->action[2];
								bro->key[2] = INT_MAX; bro->action[2] = nullptr;
								p->child[1] = bro->child[3]; bro->child[3]->parent = p; bro->child[3] = nullptr;
								if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
							}
							else { // 5 10 _
								q->key[nf] = bro->key[1]; q->action[nf] = bro->action[1];
								bro->key[1] = bro->key[0]; bro->action[1] = bro->action[0];
								bro->key[0] = INT_MIN; bro->action[0] = nullptr;
								p->child[1] = bro->child[2]; bro->child[2]->parent = p;
								bro->child[2] = bro->child[1]; bro->child[1] = bro->child[0]; bro->child[0] = nullptr;
								if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
							}
						}
						bro->num = 1;
						break;
					}
					if (nephew->num == 1) {//nephew nema dovoljno, sazimanje 
						if (q->key[0] == INT_MIN) { //p < nephew
							for (int i = 0; i < 2; i++) { q->key[i] = q->key[i + 1]; q->action[i] = q->action[i + 1]; }
							for (int i = 0; i < 3; i++) q->child[i] = q->child[i + 1];
							q->key[2] = INT_MAX; q->action[2] = nullptr; q->child[3] = nullptr;
						}
						else { // nephew < p
							for (int i = 2; i > 0; i--) { q->key[i] = q->key[i - 1]; q->action[i] = q->action[i - 1]; }
							for (int i = 3; i > 0; i--) q->child[i] = q->child[i - 1];
							q->key[0] = INT_MIN; q->action[0] = nullptr; q->child[0] = nullptr;
						}
						int nf;
						for (nf = 0; nf < 4; nf++) {
							if (q->child[nf] == p) break;
						}
						bro = nephew;
						switch (nf) {
						case 0: { //p < bro, otac je levi
							if (oldNewNode) p->action[1] = nullptr;
							delete p; q->child[0] = nullptr;
							bro->key[2] = bro->key[1]; bro->action[2] = bro->action[1];
							bro->child[3] = bro->child[2]; bro->child[2] = bro->child[1];
							bro->key[1] = q->key[0]; bro->action[1] = q->action[0];
							q->key[0] = INT_MIN; q->action[0] = nullptr;
							if (oldNewNode) { bro->child[1] = oldNewNode; oldNewNode->parent = bro; }
							break;
						}
						case 1: { //bro < p, otac je levi
							if (oldNewNode) p->action[1]; 
							else delete[] p->action[1];
							p->key[0] = bro->key[1]; p->action[0] = bro->action[1];
							p->child[0] = bro->child[1]; bro->child[1]->parent = p; bro->child[1] = nullptr;
							p->child[1] = bro->child[2]; bro->child[2]->parent = p; bro->child[2] = nullptr;
							p->key[1] = q->key[0]; p->action[1] = q->action[0];
							q->key[0] = INT_MIN; q->action[0] = nullptr;
							if (oldNewNode) { p->child[2] = oldNewNode; oldNewNode->parent = p; }
							bro->action[1] = nullptr; delete bro; q->child[0] = nullptr;
							break;
						}
						case 2: { //p < bro, otac je desni
							if (oldNewNode) p->action[1] = nullptr;
							else delete[] p->action[1];
							p->key[2] = bro->key[1]; p->action[2] = bro->action[1];
							p->child[3] = bro->child[2]; bro->child[2]->parent = p; bro->child[2] = nullptr;
							p->child[2] = bro->child[1]; bro->child[1]->parent = p; bro->child[1] = nullptr;
							p->key[1] = q->key[0]; p->action[1] = q->action[0];
							q->key[2] = INT_MAX; q->action[2] = nullptr;
							if (oldNewNode) { p->child[1] = oldNewNode; oldNewNode->parent = p; }
							bro->action[1] = nullptr; delete bro; q->child[3] = nullptr;
							break;
						}
						case 3: { //bro < p, otac je desni
							if (oldNewNode) p->action[1] = nullptr;
							delete p; q->child[3] = nullptr;
							bro->key[0] = bro->key[1]; bro->action[0] = bro->action[1];
							bro->child[0] = bro->child[1]; bro->child[1] = bro->child[2];
							bro->key[1] = q->key[2]; bro->action[1] = q->action[2];
							q->key[2] = INT_MAX; q->action[2] = nullptr;
							if (oldNewNode) { bro->child[2] = oldNewNode; oldNewNode->parent = bro; }
							break;
						}
						}
						q->num--; bro->num++;
						break;
					}
				}
			}
		}
		return true;
	}
}

void Tree::deleteActionWithHighestPriority() {
	if (root == nullptr) return;
	Node* p, *q = nullptr; int k; char* a;
	p = root;
	while (p != nullptr) {
		if (p->key[0] != INT_MIN) {	q = p;  p = p->child[0]; }
		else { q = p;  p = p->child[1]; }
	}
	p = q;
	if (p->key[0] != INT_MIN) { k = p->key[0]; a = p->action[0]; }
	else { k = p->key[1]; a = p->action[1]; }
	this->deleteAction(k, a);
	return;
}

void Tree::changeActionPriority(int k, char * a, int newk) {
	if (root == nullptr) return;
	Node* p, *q = nullptr, *newp, *newq = nullptr; int l = 1;
	p = root; newp = root;
	while (p != nullptr) {
		for (int i = 0; i < 3; i++) {
			if (p->key[i] == k && strcmp(p->action[i], a) == 0) { l = 0; q = p; p = nullptr; break; }
		}
		if (l) {
			if (k < p->key[0] || (k == p->key[0] && strcmp(a, p->action[0]) < 0)) { q = p; p = p->child[0]; }
			else {
				if (k < p->key[1] || (k == p->key[1] && strcmp(a, p->action[1]) < 0)) { q = p; p = p->child[1]; }
				else {
					if (k < p->key[2] || (k == p->key[2] && strcmp(a, p->action[2]) < 0)) { q = p; p = p->child[2]; }
					else { q = p; p = p->child[3]; }
				}
			}
		}
	}
	while (newp != nullptr) {
		if (newk < newp->key[0] || (newk == newp->key[0] && strcmp(a, newp->action[0]) < 0)) { newq = newp; newp = newp->child[0]; }
		else {
			if (newk < newp->key[1] || (newk == newp->key[1] && strcmp(a, newp->action[1]) < 0)) { newq = newp; newp = newp->child[1]; }
			else {
				if (newk < newp->key[2] || (newk == newp->key[2] && strcmp(a, newp->action[2]) < 0)) { newq = newp; newp = newp->child[2]; }
				else { newq = newp; newp = newp->child[3]; }
			}
		}
	}
	p = q; newp = newq;
	q = q->parent; newq = newq->parent;
	if (p == newp) {
		if (p->key[0] == k) {
			p->key[0] = INT_MIN;
			a = p->action[0];
			p->action[0] = nullptr;
		}
		else {
			if (p->key[2] == k) {
				a = p->action[2];
				p->key[2] = INT_MAX;
				p->action[2] = nullptr;
			}
			else {
				a = p->action[1];
				if (p->num == 1) {
					p->key[1] = INT_MAX;
					p->action[1] = nullptr;
				}
				else {
					if (p->key[2] != INT_MAX) {
						p->key[1] = p->key[2];
						p->action[1] = p->action[2];
						p->key[2] = INT_MAX;
						p->action[2] = nullptr;
					}
					else {
						p->key[1] = p->key[0];
						p->action[1] = p->action[0];
						p->key[0] = INT_MIN;
						p->action[0] = nullptr;
					}
				}
			}
		}
		p->num--;
		p->addKey(newk, a);
	}
	else {
		char * newa = new char[256];
		int i = 0;
		while (a[i] != '\0') {
			newa[i] = a[i];
			i++;
		}
		newa[i] = '\0';
		deleteAction(k, a);
		addAction(newk, newa);
	}
}
