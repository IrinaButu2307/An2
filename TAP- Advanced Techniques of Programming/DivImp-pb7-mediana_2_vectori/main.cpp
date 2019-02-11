#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readData(ifstream &fin,int &dim1, vector<int> &v1, int &dim2, vector<int> &v2) {
	fin >> dim1;
	bool cate = false;
	int x;

		for (int i = 0; i < dim1; i++) {
            fin >> x;
            v1.push_back(x);
        }
        fin >> dim2;
        for (int i = 0; i < dim2; i++) {
			fin >> x;
			v2.push_back(x);
		}
		vector<int> vaux;
		if (dim2 > dim1) {
		vaux = v1;
		v1=v2;
		v2=vaux;
		int aux = dim1;
		dim1 = dim2;
		dim2 = aux;
	}
	fin.close();
}

double median(int leftHead, int rightHead, vector<int> v) {
	int aux = (rightHead - leftHead + 1);
	int middle = (rightHead + leftHead) / 2;
	if (aux % 2 == 0)
		return (v[middle] + v[middle + 1]) / 2.0;
	else
		return v[middle];
}
/// v1 mai lung decat v2
double calculatemedian(int stg1, int dr1, int stg2, int dr2, vector<int> &v1, vector<int> &v2) {
	double med1 = median(stg1, dr1, v1);
	double med2 = median(stg2, dr2, v2);

	int cate = 0;
	int n = (dr1 - stg1 + 1);
	int m = (dr1 + stg1) / 2;

	if (dr2 - stg2 + 1 == 2) { ///daca mai sunt doar 2 elem in vectorul mai scurt

		if (v2[stg2] > med1)   cate++; else    cate--;
        if (v2[dr2] > med1)  cate++; else    cate--;

		 /// un elem mai mare si unul mai mic - mediana neschimbata
		if (cate == 0) return med1;

		/// ambele elem mai mici
		if (cate == -2)
			if ((n+2) % 2 == 0)  //verificam daca noua dimensiune
                return (v1[m - 1] + v1[m]) / 2.0;  ///MED+ANT
			else
				return v1[m - 1]; ///ANT

		///ambele elem mai mari
		if (cate == 2)
            if ((n+2) % 2 == 0)
				return (v1[m + 1] + v1[m]) / 2.0; ///MED +URM
			else
				return v1[m + 1];///URM
	}


    if (v2[dr2] > med1)         ///daca mai ramane un singur elem
		{
        if ((n + 1) % 2 == 0) //dimensiune noua vect
				return (v1[m] + v1[m + 1]) / 2.0; ///mij+ urm
			else
				return v1[m + 1];
        }
		else{
			if ((n + 1) % 2 == 0)
				return (v1[m] + v1[m - 1]) / 2.0; ///mij+ant
			else
				return v1[m-1];
            }


	if (med1 == med2)
		return med1;
	if (med1 > med2)
		return calculatemedian(stg1, stg1 + (dr2 - stg2+1) / 2, stg2 + ((dr2 - stg2 ) / 2), dr2, v1, v2);
	else
		return calculatemedian(stg1 + ((dr2 - stg2 ) / 2), dr1, stg2, stg2 + (dr2 - stg2+1) / 2,v1, v2);
}

int main(){
	vector<int> v1;
	vector<int> v2;
	int dim1, dim2;
	ifstream fin("date1.in");
	readData(fin, dim1, v1, dim2, v2);
	cout << calculatemedian(0, dim1 - 1, 0, dim2 - 1, v1, v2);

    return 0;
}
