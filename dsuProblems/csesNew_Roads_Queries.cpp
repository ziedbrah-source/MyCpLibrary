#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

typedef long long ll;
typedef long double ld;
ll n,q,d;

const ll MOD = 998244353;
ll INF=2e18;
// problem : https://cses.fi/problemset/task/2101/
// it 's a greedy problem enhanced by dsu (it will transform our graph to a tree) 
// after that we will use binary lifting to get the maximum weigth on edges
// and that max is the first day
// why ? because why we need to merge two components when we already can go there
// and this way we transform the graph to a forest :D
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
		e[x] += e[y];
		e[y] = x;
		return true;
	}
};
 
const int NAX=2e5+5;
vector<pair<ll,ll>> adj[NAX];
const int LOG=20; 
vector<int> depth(NAX);
int up[NAX][LOG];
int maximum[NAX][LOG];
void dfs(int node,int par=-1){
 
  for(int i=0;i<(int)adj[node].size();i++){
    if(adj[node][i].first==par) continue;
    depth[adj[node][i].first]=depth[node]+1;
    up[adj[node][i].first][0]=node;
    maximum[adj[node][i].first][0]=adj[node][i].second;
 
    for(int j=1;j<LOG;j++){
      ll firstpart=up[adj[node][i].first][j-1];
      up[adj[node][i].first][j]=up[firstpart][j-1];
      ll firstmax=maximum[adj[node][i].first][j-1];
      ll othermax=maximum[firstpart][j-1];
      maximum[adj[node][i].first][j]=max(firstmax,othermax);
    }
    dfs(adj[node][i].first,node);
  }
}
 
ll query(int a,int b){
  if(depth[a]<depth[b]){
    swap(a,b);
  }
  // a dima ellouta;
  int k=depth[a]-depth[b];
  int maxi=0;
  for(int i=0;i<LOG;i++){
    if(k&(1<<i)){
      maxi=max(maxi,maximum[a][i]);
      a=up[a][i];
    }
  }
  if(a==b) return maxi;
  for(int i=LOG-1;i>=0;i--){
    if(up[a][i]!=up[b][i]){
      maxi=max({maxi,maximum[a][i],maximum[b][i]});
      a=up[a][i];
      b=up[b][i];
    }
  }
  return max({maxi,maximum[a][0],maximum[b][0]});
}
void solve(){
  ll m;
  cin >> n >>m >>q;
  DSU uf(n);
  for(int i=0;i<m;i++){
    ll from,to;
    cin >> from >>to;
    from--;to--;
    if(uf.unite(from,to)){
      //uf.unite(from,to);
      adj[from].push_back({to,i+1});
      adj[to].push_back({from,i+1});
    }
  }
  set<ll> st;
  for(int i=0;i<n;i++){
    st.insert(uf.get(i));
  }
 
  for(auto el:st){
    for(int i=0;i<LOG;i++) up[el][i]=el;
    dfs(el);
  }
  for(int i=0;i<q;i++){
    ll a,b;
    cin >>a>>b;
    a--;b--;
    if(!uf.same_set(a,b)){
      cout << -1<<'\n';
      continue;
    }
    cout << query(a,b)<<'\n';
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
 
