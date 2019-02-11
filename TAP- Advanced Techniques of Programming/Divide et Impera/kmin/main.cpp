#include <iostream>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


void citire(int &n, int *&a, int &k){
	ifstream f("alkminim.in");
	f>>n;///lungimea vectorului
	a=new int[n];
	for(int i=1;i<=n;i++)
		f>>a[i];
	f>>k;
	///datele se prespupun corecte - tema: validari
}

int poz(int p, int u, int *a){
	int i=p,j=u, depli=0,deplj=-1;
	while(i<j){
		if(a[i]>a[j]){
			int aux=a[i]; a[i]=a[j];  a[j]=aux;
			//aux=depli; depli=-deplj; deplj=-aux;
			i++;
		}
		//i+=depli;j+=deplj;

		else{
            j--;
		}

	}
	return i;
}

int pozRand(int p,int u, int *a){
		srand(time(0));
		int r=rand()%(u-p+1)+p;///translatat, rezultat inte p si u
		cout<<"poz "<<r<<endl;
		int aux=a[r];a[r]=a[p];a[p]=aux;
		return poz(p,u,a);
}
/**
void afis(int n, int *a){
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}
**/
int selKMin(int p, int u, int *a, int k){
	int m=pozRand(p,u,a);

	if(m==k) return a[m];
	if(m<k) return selKMin(m+1,u,a,k);
	return selKMin(p,m-1,a,k);
}
int selKMin(int n, int *a, int k){
	return selKMin(1,n,a,k);
}
int main(){
	int n,*a,k;
	citire(n,a,k);
	cout<<selKMin(n,a,k);
///	afis(n,a);
}
