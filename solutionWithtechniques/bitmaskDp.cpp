#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
map<int,int> X;
map<int,int> Y;
map<int,int> Z;
ll dp[20][1<<20];
// problem : https://atcoder.jp/contests/abc180/tasks/abc180_e
ll getDist(int node,int node1){
	return abs(X[node]-X[node1])+abs(Y[node]-Y[node1]) + max(0,Z[node]-Z[node1]);
}
ll work(int where,int bitmask){
	if(n==__builtin_popcount(bitmask)){
		// we n
		return getDist(where,0);
	}
	if(dp[where][bitmask]!=-1) return dp[where][bitmask];
	ll answer=2e18;
	for(int i=0;i<n;i++){
		if( (bitmask & (1<<i)) !=0) continue;
			//debug() << imie(i);
			//debug() << imie(~ (1<<(i)));
			answer= min(answer,getDist(where,i)+ work(i,bitmask | (1<<(i))));
		
	}

	return dp[where][bitmask]=answer;

}
void solve(){

	cin >> n;
	memset(dp,-1,sizeof dp);
	for(int i=0;i<n;i++){
		int l,r,y;
		cin >> l >> r >> y;
		X[i]=l;Y[i]=r;Z[i]=y; // you can use arrays for better time (to remoave that log :) 
	}

	cout << work(0,1) << "\n";

	
}
	
	

 
int main() {
	int tc=1;

	while(tc--){
		solve();
	}

	return 0;
}


