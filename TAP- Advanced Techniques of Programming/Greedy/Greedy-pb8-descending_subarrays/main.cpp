#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <queue>
#include <map>
#include <unordered_map>
using namespace std;

int cautbin (vector<priority_queue<int>> v, int x, int ls, int ld)
{
    int mij;
    mij = (ls+ld)/2;
   while(ls<=ld)
   {

    if(x > -v[mij].top())
   {
       ls=mij+1;
       mij=(ls+ld)/2;
   }
    if(x<= -v[mij].top())
        return mij;
   }
    return -1;
}

int main()
{
    ifstream f("date_intrare.in");
    int i, n, j, x, val, elem;
    vector<priority_queue<int>>v(100);
    f>>n;
    f>>x;
    v[0].push(-x);
    elem=1;
    for(i=1; i<n; i++)
    {
        f>>x;
        val=cautbin(v, x, 0, elem-1);

        if(val!=-1)
            v[val].push(-x);
        else
            {
                v[elem].push(-x);
                elem++;
            }

    }
    for(i=0; i<elem; i++){
        while(!v[i].empty())
    {
        cout<<-v[i].top()<<" ";
        v[i].pop();
    }
        cout<<endl;
    }


   /// um.insert({x,priority_queue<int>(1,11)});

/*
    for(i=1; i<n; i++)
        {f>>x;
        for(auto it=um.begin(); it!=um.end(); ++it)
        {
            if(x < it->first)
            {
                um[it->first].push(x);
                while(!um[it->first])
            }

        }
        }
*/

    return 0;
}
