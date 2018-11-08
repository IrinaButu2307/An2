#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("date.in");
    int n,x,y,sala=1,act=1;
    fin>>n;
    priority_queue<pair<int,int>> p;

    for(int i=1;i<n;i++){
        fin>>x>>y;
        p.push({-x,y}); ///ord activ crescat dupa tinit
    }

     struct interval{
        int ei,ef;
    };

    vector<interval> v[100];
    priority_queue<pair<pair <int,int>,int>> d;
    pair<pair <int,int>,int>s;
    d.push({{-p.top().second, -p.top().first},sala}); ///ord activ cresc dupa tfinal
    v[1].push_back({-p.top().first,p.top().second});  ///activ care incepe cel mai devreme
    act++;
    p.pop();



       while(!p.empty()){ ///maximizez utilizarea unei zile, compar cu cel mai "liber" interval
        if(-p.top().first<-d.top().first.first){ ///verific doar daca se intersecteaza cu evenimentul care se termina cel mai devreme
            sala++; ///daca da, cresc nr de sali
            v[sala].push_back({-p.top().first,p.top().second});
            d.push({{-p.top().second, -p.top().first},sala});
        }
        else{
            s=d.top();
            d.pop();
            d.push({{-p.top().second,s.first.second},s.second}); ///actualizez cu urm activ
            ///nu voi modifica first.second pt ca trb sa retin tot intervalul orar 1-3 , 4- 8 --> 1-8
            v[s.second].push_back({-p.top().first,p.top().second});
        }
        p.pop();
    }
      cout<<sala<<endl;
    for(int i=1;i<=sala;i++){
        for(auto it:v[i])
                cout<<it.ei<<" "<<it.ef<<"; ";
       cout<<endl;
    }

    return 0;
}
