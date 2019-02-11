#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream f("date.in");
    int i, j, n, x, y;
    vector<pair<int, int>>v(30);
    int lmax[30], lungimemaxsubsir=0, poz, s=0;
    int succ[30];
    f>>n;
    for(i=1; i<=n; i++){
        f>>x>>y;
        v[i]={x,y};
        lmax[i]=0;
        succ[i]=-1;
    }
    succ[n]=n+1;
    lmax[n]=1;

    for(i=1; i<=n; i++)
        cout<<v[i].first<<" "<<v[i].second<<endl;
    ///pornesc de la sfr secv , de la penult term
    for(i=n-1; i>=1; i--){
            succ[i]=n+1;
            lmax[i]=1;
        for(j=i+1; j<=n; j++) ///merg catre sfr sirului
        {///succesorii li v[i]
            if(v[i].second==v[j].first && lmax[i]<1+lmax[j]){
                ///lungimea predecesorului creste
                lmax[i]=lmax[j]+1;
                succ[i]=j;
            }
        }
        if(lmax[i]>lungimemaxsubsir){
              lungimemaxsubsir=lmax[i];
              poz=i;
          }
    }
    cout<<"++++ SUCCESORI"<<endl;
    for(i=1; i<=n; i++)
        cout<<succ[i]<<" ";

    cout<<endl;
    cout<<"++++ LMAX"<<endl;
    for(i=1; i<=n; i++)
        cout<<lmax[i]<<" ";
   cout<<endl;

    ///nr de subsiruri cu lmax
    int nr[30]={0};
		nr[n]=1;

		for ( i=n-1;i>=1;i--){

			for(j=i+1;j<=n; j++)
				if((v[i].second==v[j].first) && (1+lmax[j]==lmax[i])){
			     	nr[i]=nr[i] + nr[j];//adun nr de subsiruri pe care le pot forma cele 2 elem
   			     }
   			if(nr[i]==0)
   			     nr[i] = 1;
		}
    for(i=1;i<=n; i++)
        if(lmax[i]==lungimemaxsubsir)
				s=s+nr[i];

    cout<<"++++ NR SUBSIRURI"<<endl;
    for(i=1; i<=n; i++)
        cout<<nr[i]<<" ";
   cout<<endl;


    ///afisare subsir de lungime maxima
    cout<<"subsirul cu lmax"<<endl;
    for (i=1;i<=lungimemaxsubsir;i++){
		   cout<<v[poz].first<<" "<<v[poz].second<<endl;
              poz = succ[poz];
		}
    cout<<"----"<<endl;
    cout<<s;
    cout<<"nr de subsiruri cu lmax "<<s;
    return 0;
}
