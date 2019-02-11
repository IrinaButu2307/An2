#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int a[100][100];
char s1[100], s2[100];

void readData(ifstream &fin, int &c1, int &c2, int &c3) {
	fin >> s1 >> s2 >> c1 >> c2 >> c3;
	cout << s1 << " " << s2 << " " << c1 << " " << c2 << " " << c3 << endl;
	fin.close();
}

pair<int, int> minim(int l, int c) { //minim intre stergere si inserare
	pair <int, int> rez;
	if (a[l - 1][c] >= a[l][c - 1]) {
		rez.first = l;
		rez.second = c - 1;
	}
	else {
		rez.first = l - 1;
		rez.second = c;
	}
	return rez;
}

int changes(int l, int c) {
	if (l == 0 && c == 0) //conditia de oprire, insemna ca am ajuns in colt st sus
		return 0;

	pair<int, int> rez;
	bool flag = false;
	if (a[l - 1][c - 1] == a[l][c] && a [l - 1][c - 1] < a[l][c - 1] && a[l - 1][c - 1] < a[l - 1][c]) {
            ///daca ult lit e coltul si coltul e si minimul

		cout << "Pastram " << s1[l - 1] << endl;
		rez.first = l - 1;
		rez.second = c - 1;
		flag = true;
		return changes(rez.first, rez.second);
	}
	if (flag == false) {
		rez = minim(l, c);
		if (a[rez.first][rez.second] > a[l - 1][c - 1]) {

			cout << "Inlocuim " << s1[l - 1] << " cu " << s2[c - 1] << endl;
			rez.first = l - 1;
			rez.second = c - 1;
		}
		else
			if (rez.first == l) //verific daca minimul este la stergere
				cout << "Inseram " << s2[c - 1] << endl;
			else
				cout << "Stergem " << s1[l - 1] << endl; //daca nu, este la inserare
    return changes(rez.first, rez.second); //apel recursiv
											   //in rez am stocat pozitiile minimului
	}
}

void levanshteinDistance(int c1, int c2, int c3) {
	int substitutionCost = c3;
	//c1 cost inserare
	//c2 cost stergere
	int n1 = strlen(s1); //dim cuv 1
	int n2 = strlen(s2); //dim cuv 2

	for (int i = 0; i <= n1; i++)
		a[i][0] = i;
	for (int j = 1; j <= n2; j++)
		a[0][j] = j; //initializari clasice

	for (int j = 1; j <= n2; j++) {
		for (int i = 1; i <= n1; i++) {
			if (s1[i - 1] == s2[j - 1])
				substitutionCost = 0; //daca sunt egale costul subst este 0
			else
				substitutionCost = c3; //daca nu este c3 care este costul subst
			a[i][j] = min(min((a[i - 1][j] + c1), (a[i][j - 1] + c2)), (a[i - 1][j - 1] + substitutionCost)); //minim din minim celor 3 posib
            //st, st sus, sus
		}
	}

	for (int j = 0; j <= n1; j++) {
		for (int i = 0; i <= n2; i++)
			cout << a[i][j] << "  ";
		cout << endl;
	}
	changes(n1, n2);
}

int main() {

	char s1[100], s2[100];
	int c1, c2, c3;
	ifstream fin("date.in");
	readData(fin, c1, c2, c3);
	levanshteinDistance(c1, c2, c3);

	return 0;
}
