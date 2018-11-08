#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("date.in");
    ofstream fout("date.out");
    int n,m,x,y,profitmax=0,termenmax=0;
    vector<pair<int, int>>a;
     vector<pair<int, int>>::iterator iter;
    priority_queue<pair<int,int>>first,second;

    fin>>n;

    for(int i=0;i<n;i++){
        fin>>x>>y;
        first.push({y,x}); ///ord descrescator in fct de timp
        a.push_back({x,y});
    }
    fin.close();
    termenmax=first.top().first;
    int v[termenmax+1]={0};
    vector<int> w;
    vector<int>::iterator it;

    while(!first.empty()){ ///mai exista elem de studiat
        while(!first.empty()&&first.top().first==termenmax){ ///scot din coada toate activ cu tmaax
            second.push({first.top().second,first.top().first});
            ///le introduc descrescator in fct de profit
            first.pop();
        }
        termenmax--; // la urm pas includem urmatoarea serie de activ cu tmax
        w.push_back(second.top().first); ///second.top()-->activitatea potrivita
        ///iter= find(a.begin(), a.end(), make_pair(second.top().second, second.top().first));
        ///cout<<"activitatea de pe pozitia"<<iter-a.begin()+1;

        profitmax+=second.top().first;
        second.pop();
    }

    cout<<profitmax<<endl;
    for( it=w.end()-1;it>=w.begin();it--)
        cout<<*it<<" ";

    fout.close();

    return 0;
}
