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
#define yes(check) cout << (check ? "YES" : "NO") << endl
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;
// problem: https://codeforces.com/contest/1986/problem/F
// basically every undirected graph have some bridges and 
// the structure is a tree of (bi connected componnets which are the new nodes) -> and then you do all tree algorithms :)
const ll MOD = 998244353;
ll INF=2e18;
const int NAX=1e5+5;
vector<ll> adj[NAX];
bool vis[NAX];
vector<int> tin, low;

vector<ll> realadjs[NAX]; // those are the bridge edges.
int timer=0;
vector<bool> visited;
map<pair<ll,ll>,bool> mp;
vector<ll> another[NAX];
void dfs(int v, int p = -1) { // bridge detection!
	//debug() << imie(v);
    visited[v] = true;
    tin[v] = low[v] = timer++;
    bool parent_skipped = false;
    for (int to : adj[v]) {
        if (to == p && !parent_skipped) {
            parent_skipped = true;
            continue;
        }
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v]){
				// this is a bridge!
				mp[{v,to}]=true;
				mp[{to,v}]=true;
				realadjs[v].push_back(to);
				realadjs[to].push_back(v);
			}
        }
    }
}
struct DSU {
	vector<int> e;
 
	// get representive component (uses path compression)
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
	void init(int N){
		e=vector<int>(N,-1);
	}
	bool same_set(int a, int b) { return get(a) == get(b); }
 
	int size(int x) { return -e[get(x)]; }
 
	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y];
		e[y] = x;
		return true;
	}
};
bool visdf1[NAX];
DSU uf;
void dfs1(int node){ // here we compress the connected component
	if(visdf1[node]) return;
	visdf1[node]=true;
	for(auto el:adj[node]){
		if(mp[{node,el}]) continue;
		uf.unite(node,el);
		dfs1(el);
	}
}
ll szz[NAX];
ll value=1e18;
ll maxi(ll value){
	return value*(value-1)/2+(n-value)*(n-value-1)/2;
}
void dfs_on_the_tree(ll node,ll par=-1){ // here we use the compressed stuff and used as a tree.
	ll represet=uf.get(node);
	szz[represet]=uf.size(node);
	ll reprpar=-1;
	
	if(par!=-1){
		reprpar=uf.get(par);
	}
	for(auto el:another[represet]){
		ll rep=uf.get(el);
		if(rep==reprpar) continue;
		dfs_on_the_tree(rep,node);
		value=min(value,maxi(szz[rep]));
		szz[represet]+=szz[rep];
	}
}
void solve(){

	ll m;
	cin >> n >>m;
	timer=0;
	uf.init(n);
	mp.clear();
	for(int i=0;i<n;i++) {
		szz[i]=0;
		visdf1[i]=0;
		another[i].clear();
		adj[i].clear();
		realadjs[i].clear();
	}
	visited.assign(n, false);
	for(int i=0;i<m;i++){
		ll from,to;
		cin >> from >>to;
		from--;to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	tin.assign(n, -1);
    low.assign(n, -1);

	
	for (int i = 0; i < n; ++i) {
        if (!visited[i])
            dfs(i);
    }

	
	for(int i=0;i<n;i++) dfs1(i);
	//debug() << imie("ha");
	// now we have the tree!
	for(int i=0;i<n;i++){
		for(auto el:realadjs[i]){
			another[uf.get(el)].push_back(uf.get(i));
			
		}
	}
	value=(n*(n-1)/2);
	dfs_on_the_tree(0);
	
	cout << value<<'\n';
	value=1e18;
//	debug() << imie(mp);



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
	cin >> tc;
    debug() << imie(tc);
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


