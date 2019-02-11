#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

vector<pair<pair<double,double>, double>> activities;
double dp[100];
double father[100];

void readData(string file,int &n){
	ifstream fin(file);
	fin >> n;
	pair<pair<double,double>, double > x;
	priority_queue<pair<pair<double, double>, double >> myqueue;
	for (int i = 0; i < n; i++) {
		fin >> x.first.first >> x.first.second >> x.second;
		myqueue.push({ { -x.first.second,x.first.first }, x.second }); ///tf, ti, profit
		///sortate cresc dupa timpul de sfarsit
	}
	activities.push_back(myqueue.top());
	myqueue.pop();
	while (!myqueue.empty()) {
		activities.push_back(myqueue.top());
		myqueue.pop();
	}
}

double binarySearch(int n) {  ///caut pana la activ i  activ comp cu ea !!!!!!!
	int i = 0;
	int j = n-1;
	int middle = (j + i) / 2;

while (i<j)
    {
		if (-activities[middle].first.first == activities[n].first.second) ///tf == ti
			return middle; ///sunt activitati comp
		if (-activities[middle].first.first > activities[n].first.second) { ///tf >ti
			j = middle - 1;
			middle = (i+j) / 2;
		}
		else{
			i = middle + 1;  /// tf< ti
			middle = (i + j) / 2;
			}
	}

 if (-activities[middle].first.first <= activities[n].first.second) /// tf<=ti
		return middle; ///cazul in care am 2 act comp dar neconsecutive
	else
		return -1;  ///cumva pt ca vreau sa epuizez optiunea de a avea tf==ti,
		/// si trb sa revin la ultima var ok
}

int planning(int n) {
	dp[0] = activities[0].second;
	int flag = 0;
	for (int i = 1; i < n; i++) {
		flag = binarySearch(i);
		if (flag == -1) { ///inseamna ca nu e comp cu nici o act
			dp[i] = max(dp[i - 1], activities[i].second);
			///max profit actual, profit strans pana la activ i-1
		}
		else {
			dp[i] = max(dp[i - 1], dp[flag] + (activities[i].second));
			///max profit dintre ce e inainte si act comp cu el plus costul ei
		}
	}

	cout<<"  ----- "<<endl;
	for (int i = 0; i < n; i++)
            cout<< -activities[i].first.first<<" "<<activities[i].first.second<<" "<<activities[i].second<<endl;
    cout<<"  ----- "<<endl;
	for (int i = 0; i < n; i++)
        cout<<dp[i]<<" ";
    cout<<endl;

	cout << "Costul total al activitatilor este " << dp[n - 1] << endl;

	int i = n - 1;
	flag = dp[n - 1];
	while ( i >= 0) {
		if (dp[i] != flag) {
			cout << activities[i + 1].first.second << " " << -activities[i + 1].first.first << endl; ///afisare invers
			flag = dp[i + 1] - activities[i + 1].second;
		}
		i--;
		/**
		ma duc in stg cat timp am valori egale pentru ca este clar ca acele activitati sunt suprapuneri
		doar prima activitate din sirul valorilor egale face parte din lista act compatibile
		1 8 8 13
		primul 8 nu e como dar ultimul da
		**/
	}
	return true;
}

int main(){
	string file = "date.in";
	int n,a;
	readData(file,n);
	planning(n);
    return 0;
}
