// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#pragma GCC optimize("O3,unroll-loops")
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
//problem : https://codeforces.com/contest/472/problem/D
//dima el sghar houmae li obviously chyet7atou fel tree.
//  O(E log V).
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
const int NAX=2e3+5;
vector<vector<pair<ll,int>>>adj1;
template <class T> T kruskal(int N, vector<pair<T, pair<int, int>>> edges) {
	sort(edges.begin(), edges.end());
	T ans = 0;
	DSU D(N + 1);  // edges that unite are in MST
	for (pair<T, pair<int, int>> &e : edges) {
		if (D.unite(e.second.first, e.second.second)) { 
			ans += e.first;
			
			adj1[e.second.first].push_back({e.first,e.second.second});
			adj1[e.second.second].push_back({e.first,e.second.first});
		}
	}
	// -1 if the graph is not connected, otherwise the sum of the edge lengths
	return (D.size(1) == N ? ans : -1);
}
ll disttt[NAX][NAX];
ll distt1[NAX][NAX];
int root=-1;
void dfs(int src,int par=-1 ){
	for(auto el:adj1[src]){
		if(get<1>(el)==par) continue;
		distt1[root][el.second] =distt1[root][src]+el.first;
		dfs(get<1>(el),src);
	}
}



void solve(){
	vector<pair<ll,pair<int,int>>> edges;
	cin >>n;
	adj1.resize(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			ll val;
			cin >> val;
			edges.push_back({val,{i,j}});
			disttt[i][j]=val;
		}
	}

	for(int i=0;i<n;i++){
		if(disttt[i][i]!=0){
			cout <<"NO"<<"\n";
			return;
		}
	}
	if(n==1){
		cout <<"YES\n";
		return;
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(i!=j){
				if(disttt[i][j]<=0 || disttt[j][i]<=0){
					cout <<"NO"<<"\n";return;
				}
			}
			if(disttt[i][j]!=disttt[j][i]){
				cout <<"NO"<<"\n";
				return;
			}
		}
	}
	long long ans=kruskal(n,edges);
	if(ans==-1){
		cout <<"NO"<<"\n";
		return;
	}
	for(int i=0;i<n;i++){
		root=i;
		dfs(root);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(distt1[i][j]!=disttt[i][j]){
				cout <<"NO"<<"\n";
				return;
			}
		}
	}

	

	cout <<"YES"<<"\n";


	
}
	
	

 
int main() {
	fastInp;
	int tc=1;
	while(tc--){
		solve();
	}

	return 0;
}

 