#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;


vector <string> subSir;
string sir;
string aux;
int dp[100] = { 0 }; ///nr minim de subsiruri la pasul i
int father[100] = { 0 }; ///vectorul de tati

void readData(vector<string>&subSir, string&sir, ifstream &fin, ifstream &fin2) {
	int n;
	string s;
	fin >> n;
	subSir.push_back("0"); ///adaug 0
	subSir.push_back("1");/// -//-
	for (int i = 0; i < n; i++) {
		fin >> s;
		subSir.push_back(s); /// pun fiecare subsir citit
	}
	fin2 >> sir;
	fin.close();
	fin2.close();
}

int subsequence() {
	dp[0] = 1; ///la prima poz e un subsir
	if (sir.find("0")==0)
		father[0] = 0; ///0 e primul subsir
	else
		father[0] = 1; ///altfel e 1
	bool flag = false;
	for (int i = 1; i < sir.size() ; i++) {
		flag = false;
		for (int j = 0; j < i; j++) {
			aux = sir.substr(j, i - j+1 ); ///alcatuiesc sirurile de la j atatea pozitii pana la i-j+1
			for (int k = 0; k < subSir.size(); k++) {
				if (subSir[k] == aux) {///se regaseste
					if (j == 0) { ///atunci de la inceput pana la i-ul curent este o secventa
						dp[i] = dp[j];
						memset(dp, 1, i-1);
					}
					else
						dp[i] = dp[j-1] + 1;///altfel cresc numarul secventelor cu 1 ptc adaugam una noua

					///de la j inainte
					flag=true;
					father[i] = k; ///tatal activitatii 1 este al k-lea subsir
					break;
				}
			}
		}
		if (flag==false)
			dp[i] = dp[i-1] + 1;
		aux.clear();
	}
	cout << endl;
	for (int i = 0; i < sir.size(); i++)
		cout << dp[i] << " ";
	int i = sir.size()-1;
	cout << endl;
	while(i>=0) {
		cout << subSir[father[i]]<<" ";
		i -= subSir[father[i]].size();
	}
	return true;
}

int main(){

	ifstream fin("date.in");
	ifstream fin2("cod.in");
	readData(subSir, sir, fin2, fin);
	subsequence();

    return 0;
}

