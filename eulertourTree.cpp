
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
const int nax=2e5+5;
ll INF=2e18;

// flattening the tree and segment tree
// objectif : get the sum of a subtree a node for every query.
// verification : https://cses.fi/problemset/result/5696646/
vector<int> vec;
vector<int> adj[nax];
int timer=0;
vector<int> st(nax);
vector<int> en(nax);
void dfs(int node,int par){
	st[node]=timer;
	debug() << imie(node);
	timer++;
	for(int i=0;i<(int)adj[node].size();i++){
		if(adj[node][i]==par) continue;
		dfs(adj[node][i],node);
	}

	en[node]=timer-1;
}
vector<ll> tree;

void point(int node ,int val){
	tree[n+node]=val;
	for(int i=(n+node)/2;i>=1;i/=2){
		tree[i]=tree[2*i]+tree[2*i+1];
	}
}

void build(){

	for(int i=n-1;i>=1;i--){
		tree[i]=tree[2*i]+tree[2*i+1];
	}
}

ll query(int node,int node_low,int node_high,int query_low, int query_high){
	if(node_low>query_high) return 0;
	if(node_high<query_low) return 0;
	if(node_low>=query_low && node_high<=query_high) return tree[node];

	int mid=(node_low+node_high)/2;
	ll firstQ=query(2*node,node_low,mid,query_low,query_high);
	ll secQ=query(2*node+1,mid+1,node_high,query_low,query_high);
	return firstQ+secQ;
}

void solve(){

	cin >> n >> q;
	vec.resize(n);
	for(int i=0;i<n;i++){
		cin >> vec[i];
	}

	
	for(int i=0;i<n-1;i++){
		int from,to;
		cin >> from >> to;
		from--;to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	int temp=n;
	while(__builtin_popcount(n)!=1){
		n++;
		vec.push_back(0);
	}
	tree.resize(2*n);
	


	dfs(0,-1);
	for(int i=0;i<temp;i++){
		tree[n+st[i]]=vec[i];
	}

	build();
debug() << imie(vec);
int cnt=0;
	for(int i=0;i<q;i++){
		int type;
		cin >> type;
		cnt++;
			debug() << imie(cnt);
		if(type==1){
			int node;int val;
			cin >> node >> val;
			node--;
			point(st[node],val);
		}else{
			int node;
			cin >> node;
			node--;
			cout << query(1,0,n-1,st[node],en[node]) << "\n";
		}
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


