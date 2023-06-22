// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,m,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
//  O(E log V).
// problem: https://cses.fi/problemset/task/1675/ 
// MST KRUSKAL
struct DSU {
	vector<int> e;

	DSU(int N) : e(N, -1) {}

	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

	bool connected(int a, int b) { return get(a) == get(b); }

	int size(int x) { return -e[get(x)]; }

	bool unite(int x, int y) {
		x = get(x), y = get(y);
		if (x == y) { return false; }
		if (e[x] > e[y]) { swap(x, y); }
		e[x] += e[y];
		e[y] = x;
		return true;
	}
};
template <class T> T kruskal(int N, vector<pair<T, pair<int, int>>> edges) {
	sort(edges.begin(), edges.end());
	T ans = 0;
	DSU D(N + 1);  // edges that unite are in MST
	for (pair<T, pair<int, int>> &e : edges) {
		if (D.unite(e.second.first, e.second.second)) { ans += e.first; }
	}
	// -1 if the graph is not connected, otherwise the sum of the edge lengths
	return (D.size(1) == N ? ans : -1);
}

void solve(){
	vector<pair<ll,pair<int,int>>> edges;
	cin >>n >> m;

	for(int i=0;i<m;i++){
		ll a,b,c;
		cin >> a >>b >> c;
		edges.push_back({c,{--a,--b}});
	}

	long long ans=kruskal(n,edges);

	if(ans>=0){
		cout << ans << "\n";
	}else{
		cout <<"IMPOSSIBLE"<<"\n";
	}

	
}
	
	

 
int main() {
	fastInp;
	int tc=1;
	while(tc--){
		solve();
	}

	return 0;
}


