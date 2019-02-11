#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

string s1, s2;
int a[20][20];
bool flag = false;

void readData(string file, string&s1, string &s2) {
	ifstream fin(file);
	fin >> s1 >> s2;
	if (s1.size() > s2.size())
		flag = true;
	else
		if (s1.size() < s2.size()) { ///preferinta personala ca primul sa fie cuv mai lung
			string aux = s1;
			s1 = s2;
			s2 = aux;
			flag = true;
		}
	fin.close();
}

int cost(char l1, char l2) { ///functie de comparat literele intre ele
	const char C = 'C';
	const char A = 'A';
	const char T = 'T';
	const char G = 'G';
	if (l1 == l2)
		return 0; ///daca sunt egale au costul 0
	if (l1 == A && l2 == C || l1 == C && l2 == A)
		return 1;
	if (l1 == G && l2 == T || l1 == T && l2 == G)
		return 1;
	return 3; ///costul altor alinieri de litere
}

void distance() {
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20 ; j++)
			a[i][j] = 8888; ///initial o valoare mare
	for (int i = 0; i <= s1.size(); i++)
		a[0][i] = 2 * i;
	for (int i = 1; i <= s2.size(); i++)
		a[i][0] = 2 * i; ///initializare cu costul spatiului

	int costMark;
	costMark = cost(s1[0], s2[0]);
	a[1][1] = costMark; ///valoarea in prima casuta
	for(int i=0;i<s1.size();i++)
		for (int j = 0; j < s2.size(); j++) {
			costMark = cost(s1[i], s2[j]); ///costul alinierii lui s1[i] cu s2[j]
			a[i][j + 1] = min(a[i][j + 1], a[i][j] + 2); //2=cost spatiu
			a[i + 1][j] = min(a[i + 1][j], a[i][j] + 2);
			a[i + 1][j + 1] = min(a[i+1][j + 1], a[i][j] + costMark);
		}
	for (int i = 0; i <= s1.size(); i++) {
		for (int j = 0; j <= s2.size(); j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl << "A fost matricea de aliniere" << endl;
}

int minim(int i, int j) {
	int val_min = min(min(a[i - 1][j], a[i][j - 1]), a[i - 1][j - 1]); ///minimul celor 3 posib
	if (val_min == a[i - 1][j - 1])
		return 0;
	if (val_min == a[i][j - 1])
		return 1;
	return 2;
	///pentru a sti in ce directie o iau cand ma intorc pentru a sti miscarile
}

int changes(int i, int j) {
	if (i == 0 || 0 == j)
		return 0;
	int contor = 0;
	if (a[i][j] == a[i - 1][j - 1])
		if (flag == false) {
			cout << "Aliniere " << s1[i - 1] << " cu " << s2[j - 1] << endl;///aceeasi litera
			changes(i - 1, j - 1);
			contor++; ///pentru a contoriza la intoarcere din recursivitate
			///sa stiu ca am intrat pe aceasta ramura
		}

	int walk;
	walk = minim(i, j);

	if (walk == 0&&contor==0) {
		cout << "Aliniere " << s1[i - 1] << " cu " << s2[j - 1] << endl;
		contor++;
		changes(i - 1, j - 1);
	}
	if (walk == 1 && contor == 0) { ///val min a[i][j-1]
		cout << "Aliniere spatiu cu " << s2[j - 1] << endl;
		contor++;
		changes(i, j - 1);
	}
	if (walk == 2 && contor == 0) { ///val min a[i-1][j]
		contor++;
		cout << "Aliniere " << s1[i - 1] << " cu spatiu" << endl;
		changes(i - 1, j);
	}
}

int main() {
	string file = "date.in";
	readData(file, s1, s2);
	cout << s1 << " " << s2 << endl;
	distance();
	cout << s1.size() << " " << s2.size()<< endl;
	changes(s1.size(), s2.size());

	return 0;
}
