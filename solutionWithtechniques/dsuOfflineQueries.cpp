//============================================================================
// Name        : Brahmi Zied
// Author      : brahZied
// Version     : 2022
// Description : Road to expert
//============================================================================
/*
    STAY ORGANIZED
    CHANGE YOUR APPROACH
    BE CONFIDENT
*/
// when you train write the algos from 0
//Think different approaches 
//(trace TestCase,think with symbols,think with PICS,
//numberTheory,bs,dp,greedy,graphs,shortest paths,mst,
//dsu,LCA(binary lifting?),hashing(strings))
//Stay Calm
// IN TRAINING DO NOT SEE WRONG TEST CASES AFTER SUBMITTING!
//Look for special cases
//Beware of overflow and array bounds
//Think the problem backwards
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
ll n,m,g,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const int MAXN = 1e6;
const ll MOD = 1e9 + 7;
ll INF=2e18;
const int NAX=2005;
struct DSU {
	vector<int> e;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

	bool same_set(int a, int b) { return get(a) == get(b); }

	int size(int x) { return -e[get(x)]; }

	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (e[x] > e[y]) swap(x, y);
		e[x] += e[y]; e[y] = x; return true;
	}
};


void solve(){
	ll q;
	cin >> n >> m >> q;
	DSU dsu(n);
	// ken ta3ref aleha b weight akther, tetkaser! 
	// donc nsortiw el edges belkbir
	// donc zeda nsortiw el queries! bel weight
	
	vector<pair<int,pair<int,int>>> Edges;
	
	for(int i=0;i<m;i++){
		int u,v,w;
		cin >> u >> v >>w;
		Edges.push_back({w,{u,v}});
	
	}
	
	
	
	sort(Edges.begin(), Edges.end(), greater < pair<int, pair<int,int>>>());
	
	vector<pair<int,pair<int,int>>> queries; // w, node, indexQuery;
	
	
	
	for(int i=0;i<q;i++){
		int node;int w;
		cin >> node >> w;
		queries.push_back({w,{node,i}});
	}
	
	sort(queries.begin(), queries.end(),greater < pair<int, pair<int,int>>>());
	int j=0;
	vector<int> ans(q,0);
	for(int i=0;i<q;i++){
		int wei=queries[i].first;
		while(Edges[j].first>=wei && j <(int)Edges.size()){
			dsu.unite(Edges[j].second.first,Edges[j].second.second);
			j++;
		}
		
		ans[queries[i].second.second]=dsu.size(queries[i].second.first);
	}
	
	for(int i=0;i<q;i++){
		cout << ans[i] << "\n";
	}
	
	


	
}

 
int main() {
	fastInp;

	//freopen("chess.in","r",stdin);
	//freopen("t.out","w",stdout);
	int tc=1;
	//debug() << imie(sieve);
	//cin >> tc;
	//int i=0;
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
