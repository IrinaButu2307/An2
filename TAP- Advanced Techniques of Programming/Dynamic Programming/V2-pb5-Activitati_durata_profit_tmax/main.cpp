#include<iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;

struct activitate{
    int profit;
    int deadline;
    int durata;
};
int dp[20][20];  ///nrlin = nractiv ; nrcol = maxDeadline
int n;
int maxDeadline; ///tmax=maxdeadline


vector <activitate> act;
priority_queue<pair <int,pair<int, int>  >> pq;

void citire (){
    ifstream f("date.in");
    int x,  p, t, l;
    f>>x;
    n=x;
    for(int i = 0; i < n; i++){
        f>>p>>t>>l;
        pq.push({-t, {p, l}}); ///sort crescat dupa deadline
    }
    while (!pq.empty()){
        act.push_back({pq.top().second.first, -pq.top().first, pq.top().second.second });
        pq.pop();
    }
    maxDeadline = act[n-1].deadline;
}
///rucsac  ob = activ, g[i] = act[i].durata, c[i] = act[i].profit, G= termlimita,,
/*
void afis(int i,int j){  //daca deadline ul ...
		if(i==0 || j==0)
			return;
		if((act[i].durata <= j)&&(dp[i][j] == act[i].profit+ dp[i-1][min(act[i].deadline, j) - act[i].durata])){
			afis(i-1,j - act[i].durata);
			cout<<i<<" "<<endl;

		}
		else
			afis(i-1,j);
}
*/
void afis (int i, int j)
{
    while(i>0 && j>0){
        if( (act[i].durata <=j) && (dp[i][j] == act[i].profit+ dp[i-1][min(act[i].deadline, j) - act[i].durata])){
            cout<<i<<" ";
            j= j-act[i].durata;
            }
        i--;
     }
}

///dp[i][j] = profit progr activ i pana la momentul j

void maxProfit(){
    int i, j, t;

    for(j = 0; j <= maxDeadline;j++){  ///prima activ e speciala
            ///recursivitatea se bazeaza pe ea, deci o tratez separat
        if(j < act[0].durata) //nu am j sa o progr
            dp[0][j] = 0;
        else
            dp[0][j] = act[0].profit;
    }
    for(i = 0; i< n; i++ ){
        dp[i][0] = 0;
    }
    for(i = 1; i < n; i++){
        for (j = 0; j<=maxDeadline; j++){
            if(j < act[i].durata)///nu pot programa, preiau dp al activitatilor de dinainte
                dp[i][j] = dp[i-1][j];
            else {
                t = min(act[i].deadline, j) - act[i].durata; ///timp incepere
                ///dar aleg in functe de profitul maxim daca progr i-1 sau i(+profit) activ pana la t
                dp[i][j] = max(dp[i-1][j], dp[i-1][t] + act[i].profit);
                }
        }
    }

    for (i = 0; i < n; i++) {
		for (j = 0; j <= maxDeadline; j++)
			cout << dp[i][j] << " ";
		cout << endl;
    }
    cout<<" PROFIT MAXIM "<<dp[n-1][maxDeadline]<<endl;
}

int main(){
    citire();
    maxProfit();
    cout<<" PROGRAMAND ACTIVITATILE ";
    afis(n, maxDeadline);

return 0;
}
