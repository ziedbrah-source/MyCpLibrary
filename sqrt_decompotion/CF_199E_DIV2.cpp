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

const ll MOD = 998244353;
ll INF=2e18;
/// problem: https://codeforces.com/contest/342/problem/E
// the idea here is to decompose the queries in sqrt(q) and 
// at each sqrt do a multisource bfs so the complexity will be:
// O(sqrt(q)*n+q*sqrt(q)*log(n));
vector<ll> queries;
const int NAX=1e5+5;
vector<ll> adj[NAX];
vector<ll> dist(NAX,INF);
const int LOG=18; 
vector<int> depth(NAX);
int up[NAX][LOG];
// verification done here : https://www.spoj.com/problems/LCASQ/ :)
void dfs(int node,int par){
	
	for(int i=0;i<(int)adj[node].size();i++){
		if(adj[node][i]==par) continue;
		depth[adj[node][i]]=depth[node]+1;
		
		up[adj[node][i]][0]=node;
		
		for(int j=1;j<LOG;j++){
			up[adj[node][i]][j]=up[up[adj[node][i]][j-1]][j-1];
		}
		
		dfs(adj[node][i],node);
	}
}

int getLCA(int node1,int node2){
	// we want node1 lower than node2 // just bech netfedew IFS;
	if(depth[node2]>depth[node1]){
		swap(node1,node2);
	}
	int k=depth[node1]-depth[node2];
	for(int i=0;i<LOG;i++){
		if(k&(1<<i)){
			node1=up[node1][i];
		}
	}
	// if they are in the same line.
	if(node1==node2){
		return node1;
	}
	// now they are in the same depth.
	for(int i=LOG-1;i>=0;i--){
		if(up[node1][i]!=up[node2][i]){
			node1=up[node1][i];
			node2=up[node2][i];
		}
	}
	
	return up[node1][0];
	
}
ll getDist(int a,int b){
  return depth[a]+depth[b]-2*depth[getLCA(a,b)];
}

void mbfs(){
  queue<int> q;
  vector<ll> tempDist(n,INF);
  vector<bool> vis(n);
  for(auto el:queries){
    q.push(el);
    tempDist[el]=0;
    vis[el]=true;
  }
  queries.clear();

  while(!q.empty()){
    int qq=q.front();
    q.pop();
    for(auto el:adj[qq]){
      if(vis[el])continue;
      tempDist[el]=tempDist[qq]+1;
      vis[el]=true;
      q.push(el);
    }
  }
  for(int i=0;i<n;i++){
    dist[i]=min(dist[i],tempDist[i]);
  }
}
void solve(){
  cin >>n >>q;
  queries.push_back(0);
  for(int i=0;i<n-1;i++){
    int from,to;
    cin >>from >>to;
    from--;to--;
    adj[from].push_back(to);
    adj[to].push_back(from);
  }
  int SQRTT=320;
  dfs(0,-1);
  mbfs();
  for(int i=0;i<q;i++){
    if((int)queries.size()>=SQRTT){
      mbfs();
    }
    int t,node;
    cin >> t >>node;
    node--;
    if(t==1){
      queries.push_back(node);
    }else{
      ll mini=dist[node];
      for(auto el:queries){
        mini=min(mini,getDist(el,node));
      }
      cout << mini<<'\n';
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


