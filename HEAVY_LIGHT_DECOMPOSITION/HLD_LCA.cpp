// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;
// problem verification : https://cses.fi/problemset/task/1688/
const ll MOD = 998244353;
ll INF=2e18;
const int NAX=2e5+5;
vector<vector<int>> adj(NAX);
vector<int> head,parent,depth,pos,heavy;
int cur_pos=0;
int dfs(int node,int par){
	int sz=1;
	int maxSubSz=0;
	for(auto el:adj[node]){
		if(el==par) continue;
		depth[el]=depth[node]+1;
		int szsub=dfs(el,node);
		parent[el]=node;
		sz+=szsub;
		if(szsub>maxSubSz){
			heavy[node]=el;
			maxSubSz=szsub;
		}
		
	}

	return sz;
}

void decompose(int node,int par){
	pos[node]=cur_pos++;
	head[node]=par;
	if(heavy[node]!=-1){
		decompose(heavy[node],par);
	}

	for(auto el:adj[node]){
		if(el==parent[node] || el==heavy[node]) continue;
		decompose(el,el);
	}
	
}

int HLD_LCA(int a,int b){
	for(;head[a]!=head[b]; ){
		if(depth[head[a]]<depth[head[b]]){
			swap(a,b);
		}
		a=parent[head[a]];

	}

	

	if(depth[a]>depth[b]){
			swap(a,b);
	}
	return a;


}
void init(){
	head=vector<int>(NAX);
	parent=vector<int>(NAX);
	depth=vector<int>(NAX);
	pos=vector<int>(NAX); // pos of bla bla in the segment tree.
	heavy=vector<int>(NAX,-1);
	cur_pos=0;
	dfs(0,-1);

	decompose(0,0);
	
}
void solve(){
	int q;
	cin >> n;
	cin >> q;

	for(int i=1;i<n;i++){
		int boss;
		cin >> boss;
		boss--;
		adj[i].push_back(boss);
		adj[boss].push_back(i);
	}
	init();
	for(int i=0;i<q;i++){
		int a,b;
		cin >> a >> b;
		a--;b--;
		cout <<HLD_LCA(a,b)+1<<"\n";
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
	//cin >> tc;
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

