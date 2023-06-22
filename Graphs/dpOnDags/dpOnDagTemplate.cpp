// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,m,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;
//problem : https://cses.fi/problemset/task/1680/
// topic: dp on dag
const ll MOD = 998244353;
ll INF=2e18;
const int NAX=1e5+5;
vector<bool> vis(NAX);
vector<int> topo;
vector<int> adj[NAX];
void dfs(int node){
	vis[node]=true;
	for(auto el:adj[node]){
		if(vis[el])continue;
		dfs(el);
	}
	topo.push_back(node);
}
ll dp[NAX]; // dp[i]=max flights bech touseli fel dag
void solve(){

	cin >> n >> m;
	for(int i=0;i<m;i++){
		int from,to;
		cin >> from >> to;
		from--;to--;
		adj[from].push_back(to);
	}


	for(int i=0;i<n;i++){
		if(vis[i]) continue;
		dfs(i);
	}
	reverse(topo.begin(),topo.end());
	vector<int> nodeToIndex(n);
	for(int i=0;i<n;i++){
		nodeToIndex[topo[i]]=i;
	}

	for(int i=0;i<n;i++){
		dp[i]=-INF;
	}
	dp[0]=1;
	vector<int> prev(n);
	for(int i=0;i<n;i++){
		prev[i]=i;
	}
	for(int i=nodeToIndex[0];i<n;i++){
		int node=topo[i];
		for(auto el:adj[node]){
			
			if(dp[node]+1>dp[el]){
				prev[el]=node;
			}
			dp[el]=max(dp[el],dp[node]+1);
		}
	}
	vector<int> res;
	int val=n-1;
	res.push_back(val);
	while(prev[val]!=val){
		val=prev[val];
		res.push_back(val);
	}
	reverse(res.begin(),res.end());
	if(val!=0){
		cout <<"IMPOSSIBLE"<<"\n";
	}else{
		cout <<res.size()<<"\n";
		for(auto el:res){
			cout << el+1 << " ";
		}
		cout <<"\n";
	}




	
}
	
	

 
int main() {
	fastInp;
	//init();
	//debug() << imie(s);
	//freopen("grids.in","r",stdin);
	//freopen("res.out","w",stdout);
	// __gcd <long long> (x, y);
	int tc=1;
	//debug() << imie(sieve);
//	cin >> tc;
	//cout << setprecision(10)<<fixed;

	while(tc--){
		//i++;
		//cout <<"Test " << i << ":" << "\n";
		
		solve();
		
	}

	return 0;
}

/*
   Some insights:
    .Binary search
    .Graph representation
    .Write brute force code
    .Change your approach
 
 
 */

