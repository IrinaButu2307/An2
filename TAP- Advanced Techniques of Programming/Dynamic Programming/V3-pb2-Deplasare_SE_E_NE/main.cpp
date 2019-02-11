#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std;
int s[100][100]={0};
int t[100][100]={0};
int succ[100][100]={0};
int pred[100][100]={0};
int u[100][100]={0};
int main()
{
 ifstream f("date.in");
    int i, j;
    int n, m, maxim=0, pozi, pozj, pozifin;

    f>>n>>m;
    for(i=1; i<=n; i++)
        for(j=1; j<=m; j++)
            f>>t[i][j];

    for(i=1; i<=n; i++){ ///de pe prima col pornesc si nu am ce modif
       s[i][1]=t[i][1];
    }
    for(j=2; j<=m; j++)
        for(i=1; i<=n; i++){
            ///mergand spre E iau ce e inainte ->V
            ///SE-> ce e la NV??
            ///NE-> ce e la SV
                if(s[i][j-1]>= s[i-1][j-1] && s[i][j-1]>= s[i+1][j-1])
                  pred[i][j]=0;

                if(s[i-1][j-1]>= s[i][j-1] && s[i-1][j-1]>= s[i+1][j-1])
                    pred[i][j]=1;

                if(s[i+1][j-1]>= s[i][j-1] && s[i+1][j-1]>= s[i-1][j-1])
                   pred[i][j]=2;

           s[i][j]= max(max(s[i][j-1], s[i-1][j-1]), s[i+1][j-1]) +t[i][j];
        }
    for(i=1; i<=n; i++)
       if(maxim <s[i][m]){
                maxim=s[i][m];
                pozi=i;
                pozj=m;
            }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++)
            cout<<s[i][j]<<" ";
        cout<<endl;
        }
     for(i=1;i<=n;i++){
        for(j=1;j<=m;j++)
            cout<<pred[i][j]<<" ";
        cout<<endl;
        }
    cout<<"Suma maxima e "<<maxim<<endl;

 cout << "Traseu: " << endl;
	j = pozj;
	i= pozi;
		while(j>1 && i>1)
    {
        if(pred[i][j]==1) //(adica daca merg catre SE)
            i--;
        if(pred[i][j]==2) //(adica daca merg catre NE)
            i++;
        j--;

    }
    cout<<i<<" "<<j;




return 0;
}
