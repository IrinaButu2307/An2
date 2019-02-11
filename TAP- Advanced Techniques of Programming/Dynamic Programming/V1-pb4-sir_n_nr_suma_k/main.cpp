#include <iostream>
#include <fstream>
#include <vector>
//#include <string>
using namespace std;

int main()
{
    ifstream f("date.in");
    ofstream g("date.out");
    int i, j, n, x, k, elem, lin, dim, corespondent;
    f>>n>>k;
    int a[n][k+1];
    vector <int> v;
    vector <int> aux;
     for(i=0; i<n; i++)
        for(j=0; j<=k; j++)
            a[i][j]=0;


    f>>dim;
    for(j=0; j<dim; j++){ ///completarea primei linii
        f>>x;
        v.push_back(x);
        if(x<=k)
            a[0][v[j]]=x;
        }
    lin=0;
    v.erase(v.begin(), v.end());
    while(!f.eof()){
        int ant=lin;
        lin++; ///linia care urmeaza sa fie compl

        f>>dim;
        for(j=0; j<dim; j++){
            f>>x;
            v.push_back(x); ///noul vector adaugat pe  lin
        }

        for(i=0; i<v.size(); i++)
            for(j=0; j<=k; j++)
                if( a[ant][j] != 0 ) ///val nenula
                    if( v[i]+j <= k ) ///val curenta + col termenului nenul <=k
                        a[lin][v[i] + j] = v[i]; ///cand ma intorc fac pasul inapoi pe v ant fix de masura v[i]

        v.erase(v.begin(), v.end());
    }
    for(i=0; i<n; i++){
        for(j=0; j<=k; j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }

    ///merg pe ult lin si iau coresp lui k
    lin=n-1;
    cout<<a[lin][k]<<" "; /// 2/// va fi clar in secv

    while(lin>0){
        k=k-a[lin][k]; ///11-2 =9  //nr de col se va micsora, caut in urma
        lin--; ///caut cu o linie mai sus
        cout<<a[lin][k]<<" ";
    }


    return 0;
}
