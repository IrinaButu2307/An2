#include <iostream>
#include <vector>
#include <fstream.>
#include <cstdlib>
#include<ctime>
using namespace std;

int readData(ifstream &fin, int &n, vector<pair<int, double>> &values) {
	fin >> n;
	int number;
	double pond;
	for (int i = 0; i < n; i++) {
		fin >> number;
		values.push_back({ number,0 });
	}
	for (int i = 0; i < n; i++) {
		fin >> pond;
		values[i].second = pond; ///atasez ponderile
	}
	fin.close();
	return true;
}

afisvector(int p,int u,vector<pair<int, double>> v){
	int i, n=v.size();
	for(i=p;i<=u;i++)
		cout<<v[i].first<<"   ";
	cout<<endl;
	for(i=p;i<=u;i++)
		cout<<v[i].second<<" ";
		cout<<endl;
}

int poz(int p,int r ,int u, vector<pair<int, double>> &a,double &leftSum, double &rightSum) {
	cout<<" valoare pivot " <<a[p].first;          ///rand a scos un pivor, l-am fixat pe prima poz, acum fac QUICKSORT
	int i = p, j = u, depli = 0, deplj = -1,aux2;
	if (j - i == 1)
		if (a[i].first > a[j].first) //!!!pivotare dupa first, nu dupa second (dupa valoare, nu dupa pondere)
			return i;
		else
			return j;

	while (i<j) {
		if (a[i].first > a[j].first) {
			pair<int,double> aux = a[i];
			a[i] = a[j];
			a[j] = aux;
			aux2 = depli;
			depli = -deplj;
			deplj = -aux2;
		}
		i += depli; j += deplj;
	}
	r = i;
	cout<<" adus pe pozitia "<<r<<endl;  ///acum pivotul r, e pe alta pozitie, ordonat cf QUICKSORT
	afisvector(p,u,a);
	leftSum = 0;
	rightSum = 0;
	for (int i = p; i < r; i++)
		leftSum += a[i].second;
	for (int i = r + 1; i <=u; i++)
		rightSum += a[i].second;
    return r;


//!!!trebuie intoarsa pozitia pivotului, indiferent cum este suma pe stanga sau dreapta, pt ca
///adaugi "suma celor la care voi renunta" in v[median]; daca median=-2, atunci acceseaza v[-2] si da eroare
}

int pozRand(int p, int u, vector<pair<int,double>> &a,double &leftSum, double &rightSum) {
	srand(time(0));
	int r = rand() % (u - p + 1) + p;//translatat, rezultat inte p si u
	cout << "r=" << r;
	cout << "aici" << endl;
	pair<int,double> aux = a[r];
	a[r] = a[p];
	a[p] = aux;
	return poz(p,r,u, a,leftSum, rightSum);
}

int calculateMedian(vector<pair<int, double>> &values, int leftHead, int rightHead, double &leftSum, double &rightSum) {
	int median;
	cout<<endl<<"subproblema curenta "<<leftHead<<" "<<rightHead<<endl;

	if(rightHead-leftHead==0) /// 1 elem
		return values[leftHead].first;
	if(rightHead-leftHead==1)  /// 2 elem
		if(values[rightHead].second<=0.5)
			return values[leftHead].first;
		else
			return values[rightHead].first;

    if(rightHead-leftHead>1){ /// >2 elem

	median = pozRand(leftHead, rightHead,values,leftSum, rightSum);
	cout<<" cele doua sume "<<leftSum<<" "<<rightSum<<endl;

	if (rightSum > 0.5) {
		values[median].second += leftSum; ///salvez suma celor la care voi renunta in v[median]
		///ma voi repozitiona catre dreapta si nu mai are sens sa retin ce a fost in stanga
		return calculateMedian(values, median,rightHead,leftSum, rightSum);
	}
	if (leftSum >= 0.5) {
		values[median].second += rightSum; ///salvez suma celor la care voi renunta in v[median]
		return calculateMedian(values, leftHead,median,leftSum, rightSum);
	}
    }

	return values[median].first;
}
int main()
{
	ifstream fin("date.in");
	vector<pair<int, double>> values;
	int number;
	double leftSum = 0, rightSum = 0;
	readData(fin, number, values);
	int x=calculateMedian(values, 0, number-1,leftSum,rightSum);
	cout<<endl<<x;

	return 0;
}
