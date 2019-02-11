#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

void citire(int &n, int *&a){
	ifstream f("date2.in");
	f>>n;//lungimea vectorului
	a=new int[n];
	for(int i=0;i<n;i++)
		f>>a[i];
}

int interclasare(int p,int m,int u, int *a){
	int *b=new int[u-p+1];
  	int i=p,j=m+1, k=0,nr=0;
  	int poz;
   	while ((i<=m)&&(j<=u)){
        cout<<"    studiez"<<a[i]<<"  "<<a[j]<<endl;

    	if (a[i]<=2*a[j]){
                b[k]=a[i];
                i++;
        }
		else{ ///if(a[i]>2*a[j]
                poz=i;
                b[k]=a[j];
                j++;
        		nr = nr + (m-poz+1);
        		cout<<m-poz+1<<endl;
        	}
    	k++;
    }
   	while(i<=m){ b[k]=a[i]; k++; i++; }
   	while(j<=u){ b[k]=a[j]; k++; j++; }
	for (i=p;i<=u;i++)
     	a[i]=b[i-p];
	return nr;
}

int nrInv(int p,int u, int *a){
   if (p == u){
       return 0;
   }
   else {

   	    int m = (p+u)/2;
        int n1 = nrInv(p,m,a);
        int n2 = nrInv(m+1,u,a);
        return interclasare(p,m,u,a)+n1+n2;
   }
}

int nrInv(int n, int *a){
	return nrInv(0,n-1,a);
}

void afis(int n,int *a){
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

 int main( ){
 	int n, *a;
	citire(n,a);
 //	cout<<"nr de inversiuni calculat cu algoritmul n^2: "<<nrInvComplex(n,a)<<endl;
	cout<<"nr de inversiuni calculat cu interclasare: "<<nrInv(0,n-1,a)<<endl;
	return 0;
 }
/*
#include <iostream>
#include <fstream>
using namespace std;

void citire(int &n, int *&a){
	ifstream f("date.in");
	f>>n;//lungimea vectorului
	a=new int[n];
	for(int i=0;i<n;i++)
		f>>a[i];
}

int interclasare(int p,int m,int u, int *a){
	int *b=new int[u-p+1];
  	int i=p,j=m+1, k=0,nr=0;
   	while ((i<=m)&&(j<=u)){
                        cout<<"      studiez"<<a[i]<<"  "<<a[j]<<endl;

    	if (a[i]<=a[j]){ b[k]=a[i]; i++; cout<<"pun "<<b[k]<<endl;}
		else{ b[k]=a[j]; j++;
        		nr = nr + (m-i+1);cout<<"m este "<<m<<endl; ///toate elem pana la m sunt sortate
        		/// iar la i il gasesc pe primul mai mare
        		cout<<"nr inv este "<<nr<<" "<<endl;
        		cout<<"pun "<<b[k]<<endl;
        	}
    	k++;
    }
   	while(i<=m){ b[k]=a[i]; k++; i++; }
   	while(j<=u){ b[k]=a[j]; k++; j++; }
	for (i=p;i<=u;i++)
     	a[i]=b[i-p];
	return nr;
}

int nrInv(int p,int u, int *a){
   if (p == u){
       return 0;
   }
   else {

   	    int m = (p+u)/2;
        int n1 = nrInv(p,m,a);
        int n2 = nrInv(m+1,u,a);
        return interclasare(p,m,u,a)+n1+n2;
   }
}

int nrInv(int n, int *a){
	return nrInv(0,n-1,a);
}

void afis(int n,int *a){
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
}

 int main( ){
 	int n, *a;
	citire(n,a);
 //	cout<<"nr de inversiuni calculat cu algoritmul n^2: "<<nrInvComplex(n,a)<<endl;
	cout<<"nr de inversiuni calculat cu interclasare: "<<nrInv(0,n-1,a)<<endl;
	return 0;
 }
*/
