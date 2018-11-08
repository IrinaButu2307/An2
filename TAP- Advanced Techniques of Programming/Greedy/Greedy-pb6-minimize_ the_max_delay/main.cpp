#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

int main()
{
    ifstream f("date.in");
    priority_queue <pair<int, int>> q;
    vector <pair<int, int>> indici;
    int timp, maxim, n, i, l, t ;

    f>>n;
    for(i=0; i<n; i++)
    {
        f>>l>>t;
        indici.push_back({l,t});
        q.push({-t, l});
    }
    t=0;
    priority_queue<int> intarziere;
    while (!q.empty())
  {
    cout<<"interval "<<t<<" "<<t+q.top().second<<endl;
    t+=q.top().second; ///lungimea
    intarziere.push(t-(-1)*q.top().first);
    q.pop();
  }

  cout<<"intarzierea minima"<<intarziere.top();

    ///adunari clasice pana la terminarea queue



    return 0;
}
