#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;
int number=1,k2;

void citire(int &n, ifstream &fin){
    fin>>n;
    fin.close();
}

int ** createMatrix (int &n){
    int k=pow(2,n);
    k2=k;
    cout<<"k="<<k<<endl;
    n=k;
    int** a=new int * [k];
    for(int i=0;i<n;i++)
        a[i]=new int [k];
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
            a[i][j]=0;
    return a;
}

int completeMatrix(int **a, int n, int l, int c,int &number){
    if(n==1){
        a[l][c]=number;
        number++;
    }
    else{ //vezi figura lab
        completeMatrix(a,n/2,l,c+n/2,number); ///cadran 2
        completeMatrix(a,n/2,l+n/2,c,number); ///cadran 3
        completeMatrix(a,n/2,l,c,number); ///cadran 1
        completeMatrix(a,n/2,l+n/2,c+n/2,number); ///cadran 4
    }
}

int main()
{
    ifstream fin("fisier.in");
    int n;
    citire(n,fin);
    int **a;
    a=createMatrix(n);
    completeMatrix(a,n,0,0,number);
    cout<<"n="<<n<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<a[i][j]<<"   ";
        cout<<endl;
    }
    return 0;
}
