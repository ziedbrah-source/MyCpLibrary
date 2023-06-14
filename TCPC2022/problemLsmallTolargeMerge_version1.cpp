// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
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
#define         aff(v) for(auto e:v) cout<<e<<" ";cout<<endl;
#define mem1(a)           memset(a,-1,sizeof(a))
#define mem0(a)           memset(a,0,sizeof(a))
#define all(x)            (x).begin(),(x).end()
#define sz(x)             (int)((x).size())
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
// let f(u)=numberof white - numbers of blacks in the path from 1 to u.
const int nax=2e5;
int id[nax];
int color[nax];
vector<int> adj[nax];
vector<int> queries[nax];
int ans[nax];
map<int,int> freq[nax];
void mrg(int u,int v){
	  if (freq[id[u]].size() < freq[id[v]].size()) {
        swap(id[u], id[v]);
    }
    for (auto x : freq[id[v]]) {
        freq[id[u]][x.first] += x.second;
    }
}
void dfs(int node,int count,int par){
	ll anss=0;
	for(auto v:adj[node]){
		if(v==par) continue;
		dfs(v,count+color[node],node);
		anss+=freq[id[v]][count];
		mrg(node,v);
	}

	for(auto q:queries[node]){
		ans[q]=anss;
	}
	freq[id[node]][count+color[node]]++;
}
void solve(){
	ll q;
	cin >> n >> q;

	for(int i=0;i<n;i++){
		cin >> color[i];
		if(color[i]==0) color[i]=-1;
		id[i]=i;
	}
	for(int i=0;i<n-1;i++){
		int from,to;
		cin >> from >> to;
		from--;to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}


	for(int i=0;i<q;i++){
		int node;
		cin >> node;
		node--;
		queries[node].push_back(i);
	}
	dfs(0,0,-1);

	for(int i=0;i<q;i++){

		cout << ans[i] << "\n";

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

