// THEY DON'T KNOW ME SON
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

typedef long long ll;
typedef long double ld;
ll n,q,d,m;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
const int NAX=2e5+5;
vector<vector<int>> depths(NAX);
// problem : https://codeforces.com/group/CQhYdQCAxh/contest/424083/problem/F
vector<int> depthV(NAX);
vector<int> adj[NAX];
int st[NAX];
int en[NAX];
int timer=0;
void dfs(int node,int par){
	st[node]=timer;
	timer++;
	if(par!=-1){
		depthV[node]=1+depthV[par];
	}else{
		depthV[node]=0;
	}

	depths[depthV[node]].push_back(st[node]);
	for(auto el:adj[node]){
		dfs(el,node);
	}


	en[node]=timer;
}
void solve(){
	cin >> n;	
	for(int i=0;i<n-1;i++){
		int par;
		cin >> par;
		par--;
		adj[par].push_back(i+1);
		//adj[i+1].push_back(par);
	}
	dfs(0,-1);
	

	
	cin >>q;
	debug() << imie(q);
	while(q--){
		int node;int dep;
		cin >> node >> dep;
		node--;
		int star=st[node];
		int endd=en[node];
		auto it=lower_bound(depths[dep].begin() ,depths[dep].end(),endd);
		auto it1=lower_bound(depths[dep].begin(),depths[dep].end(),star);
		cout << it-it1 << "\n";

	}


}
	
	

 
int main() {
	fastInp;
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

