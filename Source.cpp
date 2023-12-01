#include "Tree234.h"
#include "BinaryTree.h"

int main() {
	int flag = 1, u, k, n, newk, i; bool l;
	string s; char* a = nullptr, c;
	Tree *t = nullptr; BinaryTree *tb;
	cout << "Meni:" << endl << "1. Stvori stablo iz datoteke" << endl << "2. Ispisi 2-3-4 stablo" << endl << "3. Ubaci akciju" << endl;
	cout << "4. Pretrazi stablo po prioritetu akcije" << endl << "5. Brisanje proizvoljne akcije po prioritetu";
	cout << endl << "6. Brisanje akcije najvise prioriteta" << endl << "7. Ispisi crveno-crno stablo" << endl;
	cout << "8. Izmeni prioritet akcije" << endl << "9. Pronalazenje broja akcija sa zadatim prioritetom" << endl;
	cout << "0. Kraj programa" << endl;
	while (flag) {
		printf("\nOdaberite stavku iz menija: ");
		scanf("%d", &u);
		switch (u) {
		case 1: { //Stvori stablo iz datoteke
			t = new Tree;
			cout << "Unesite ime datoteke iz koje se citaju podaci o akcijama: ";
			cin >> s;
			t->create234Tree(s);
			cout << "Stablo je formirano" << endl;
			break;
		}
		case 2: { // Ispisi 2-3-4 stablo
			if (t != nullptr) {
				t->printTree();
				cout << endl;
			}
			break;
		}
		case 3: { //Ubaci akciju
			cout << "Unesite prioritet akcije: ";
			cin >> k;
			cout << "Unesite akciju: ";
			a = new char[256];
			c = getchar(); i = 0;
			while ((c = getchar()) != '\n') {
				a[i] = c;
				i++;
			}
			a[i] = '\0';
			if (t == nullptr) {
				t = new Tree;
			}
			t->addAction(k, a);
			cout << "Akcija je uneta." << endl;
			break;
		}
		case 4: { //Pretrazi stablo po prioritetu akcije
			cout << "Unesite prioritet akcije: ";
			cin >> k;
			string s1 = t->findAction(k);
			cout << "Pronadjena je akcija ";
			cout << s1;
			cout << " sa zadatim prioritetom" << endl;
			break;
		}
		case 5: { //Brisanje proizvoljne akcije po prioritetu
			cout << "Unesite prioritet akcije: ";
			cin >> k;
			cout << "Unesite akciju: ";
			a = new char[256];
			c = getchar(); i = 0;
			while ((c = getchar()) != '\n') {
				a[i] = c;
				i++;
			}
			a[i] = '\0';
			l = t->deleteAction(k, a);
			if(l) cout << "Akcija je izbrisana." << endl;
			else cout << "Akcija nije pronadjena." << endl;
			break;
		}
		case 6: { //Brisanje akcije najvise prioriteta 
			t->deleteActionWithHighestPriority();
			cout << "Akcija sa najvisim prioritetom je izbrisana." << endl;
			break;
		}
		case 7: { //Ispisi crveno-crno stablo
			tb = new BinaryTree;
			tb->createBinaryTree(*t);
			cout << endl;
			tb->printBinaryTree();
			break;
		}
		case 8: { //Izmeni prioritet akcije
			cout << "Unesite prioritet akcije: ";
			cin >> k;
			cout << "Unesite akciju: ";
			a = new char[256];
			c = getchar(); i = 0;
			while ((c = getchar()) != '\n') {
				a[i] = c;
				i++;
			}
			a[i] = '\0';
			cout << "Unesite novi prioritet akcije: ";
			cin >> newk;
			t->changeActionPriority(k, a, newk);
			cout << "Prioritet akcije je promenjen." << endl;
			break;
		}
		case 9: { //Pronalazenje broja akcija sa zadatim prioritetom
			cout << "Unesite prioritet akcije: ";
			cin >> k;
			n = t->countKeys(k);
			cout << "Broj pronadjenih akcija je " << n << "." << endl;
			break;
		}
		case 0: { //kraj
			flag = 0;
			if(t != nullptr) t->deallocateTree();
			//tb->deallocateBinaryTree();
			break;
		}
		default: {
			printf("Uneta opcija ne postoji u meniju, pokusajte ponovo\n");
		}
		}
	}
	return 0;
}