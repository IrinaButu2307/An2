#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <math.h>

using namespace std;

int main()
{
    ifstream f("date.in");
    int i, j;
    int n, m;
int s[100][100];
int t[100][100];
int succ[100][100];
int u[100][100];
    f>>n>>m;
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
           {
            f>>t[i][j];
           // succ[i][j]=-1;
           }

    s[0][0]=t[0][0];

    for(j=1; j<m; j++)
        s[0][j]=s[0][j-1]+ t[0][j]; //prima lin

    for(i=1; i<n; i++)
        s[i][0]=s[i-1][0]+ t[i][0]; //prima col

    if(s[0][1] >= s[1][0]) //val mai mare linie decat pe col
        succ[0][0] = 0; // sch col ->merg in dr
    else
        succ[0][0] = 1; //merg in jos->1

    for(i=1; i<n; i++)
        for(j=1; j<m; j++){ /// PRIVESC INVERS, CATRE NORD SI VEST
           if(s[i-1][j] >= s[i][j-1])
                succ[i-1][j]=1;  //cobor pe urm linie
            else
                succ[i][j-1]=0; //schimb coloana
            s[i][j]=max(s[i-1][j], s[i][j-1])+ t[i][j];
        }


    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
            cout<<s[i][j]<<" ";
        cout<<endl;
        }
    for(i=0;i<n;i++){
        for(j=0;j<m;j++)
            cout<<succ[i][j]<<" ";
        cout<<endl;
        }
    cout<<"suma maxima "<<s[n-1][m-1]<<endl;
    cout << "Traseu: " << endl;

    i=0;j=0;
    succ[n-1][m-1]=-1; //finish
    while(succ[i][j]!=-1) //nu am aj la finish
    {
        cout<<i+1<<" "<<j+1<<endl;
                 if(succ[i][j]==0)
            j++; //schimb coloana
        else i++; //schimb linia
    }
    cout<<i+1<<" "<<j+1;


    return 0;
}

