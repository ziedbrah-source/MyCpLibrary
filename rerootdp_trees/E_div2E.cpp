#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

typedef long long ll;
typedef long double ld;
ll n,d;

// problem: https://codeforces.com/contest/1187/problem/E it's dp with rerooting :)
// basically rerooting is to solve the problem for every root possible!
// the reroot is easy, just consider modifying only teh children as if the parent is root now w ki tetbadel el hesba ech ysir! and thats it it works khater kol mara taaref eli bouk howa root w 
// valeur eli fih shiha for sure!
const int NAX=2e5+5;
vector<ll> adj[NAX];
ll dpsz[NAX];
ll dp[NAX];
void dfs(ll node,ll par=-1){
	dpsz[node]=1;
	for(auto el:adj[node]){
		if(el==par) continue;
		dfs(el,node);
		dpsz[node]+=dpsz[el];
	}
	
	dp[node]+=dpsz[node];
	for(auto el:adj[node]){
		if(el==par) continue;
		dp[node]+=dp[el];
	}
	
}
ll maxi=0;

void reroot(ll node,ll par=-1){
	for(auto el:adj[node]){
		if(el==par) continue;
		dp[el]=dp[node]-2*dpsz[el]+n; // just badel el formule lehné fi kol prob ..
		maxi=max(maxi,dp[el]);
		reroot(el,node);
	}
}
void solve(){

	cin >> n;
	for(int i=0;i<n-1;i++){
		ll from,to;
		cin >> from >>to;
		from--;to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	dfs(0);
	maxi=dp[0];
	reroot(0);
	cout << maxi <<'\n';

}
	
	

 
int main() {
	fastInp;
//	
	int tc=1;
	

	while(tc--){
		
		
		solve();
		
	}

	return 0;
}

