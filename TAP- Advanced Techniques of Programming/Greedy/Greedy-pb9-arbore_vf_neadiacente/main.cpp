#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

vector <list<int>>l(100);
vector <int> tata(100);
vector <int> viz(100);
vector <int> d(100);
vector <int>v(200); //poz=1 -nu poz=0 da

queue <int> q;

void bf(int start, int n)
{
    int u, v, aux;
    d[start]=0;
    tata[start]=0;
    viz[start]=1;
    q.push(start);
    while (!q.empty())
    {
        u=q.front();
        q.pop();

        for(int i:l[u])
            if(viz[i]==0)
            {
                tata[i]=u;
                viz[i]=1;
                d[i]=d[u]+1;
                q.push(i);
            }
    }
}


int main()
{
   int i, n, x, y, cate=0;
   ifstream f("date.in");
   priority_queue <pair<int, int>>pq;

   f>>n;
   for(i=0; i<n; i++)
   {
       f>>x>>y;
       l[x].push_back(y);
       l[y].push_back(x);
   }
   bf(1,n);
   for(i=1; i<=n; i++)
    cout<<i<<" "<<d[i]<<" "<<tata[i]<<endl;
   cout<<endl;
   for(i=1; i<=n; i++)
    {
        pq.push({d[i],i}); /// distanta pana la rad si nodul
    }
    cout<<"top:"<<pq.top().second<<endl;
   while(!pq.empty())
   {
       if(v[pq.top().second]==0)
       {
           cate++;
       cout<<pq.top().second;

       v[tata[pq.top().second]]=1;
       }
    pq.pop();

   }
cout<<cate;


    return 0;
}
