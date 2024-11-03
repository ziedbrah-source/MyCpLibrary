#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
#define yes(check) cout << (check ? "Yes" : "No") << endl
typedef long long ll;
typedef long double ld;
ll n,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;

// __builtin_popcount() Function
// you use this technique when you have queries on a tree and he gives k nodes each time -> you create the new tree (in O(k) and you you do some dp or smth on it and you get the result)
// the problem : https://codeforces.com/contest/613/problem/D
const int mxN=1e5+5;
vector<int> adj[mxN];
const int LOG=18; 
vector<int> depth(mxN);
int up[mxN][LOG];
int st[mxN];
int en[mxN];
int timer=0;
int parr[mxN];
// verification done here : https://www.spoj.com/problems/LCASQ/ :)
void dfs(int node,int par=-1){
	st[node]=timer;
	timer++;
	parr[node]=par;
	for(int i=0;i<(int)adj[node].size();i++){
		if(adj[node][i]==par) continue;
		depth[adj[node][i]]=depth[node]+1;
		
		up[adj[node][i]][0]=node;
		
		for(int j=1;j<LOG;j++){
			up[adj[node][i]][j]=up[up[adj[node][i]][j-1]][j-1];
		}
		
		dfs(adj[node][i],node);
	}
	en[node]=timer;
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
vector<bool> is_important(mxN);
vector<ll> vt_tree[mxN];
ll dp[mxN][2];

vector<ll> choosenVertices;
bool cmp(int u,int v){
	return st[u]<st[v];
}
bool upper(int u,int v){
	return st[u]<=st[v] && en[v]<=en[u]; 
}
int create_vt_tree(){

	sort(all(choosenVertices),cmp);
	int k=sz(choosenVertices);
	for(int i=0;i<k-1;i++){
		int new_verttex=getLCA(choosenVertices[i],choosenVertices[i+1]);
		choosenVertices.push_back(new_verttex);
	}
	sort(all(choosenVertices),cmp);
	choosenVertices.erase(unique(all(choosenVertices)),choosenVertices.end());

	vector<int> stack_of_vertices;
	stack_of_vertices.push_back(choosenVertices[0]);
	for(int i=1;i<sz(choosenVertices);i++){
		int u=choosenVertices[i];
		while(sz(stack_of_vertices)>=2 && !upper(stack_of_vertices.back(),u)){
			vt_tree[stack_of_vertices[sz(stack_of_vertices)-2]].push_back(stack_of_vertices.back());
			stack_of_vertices.pop_back();
		}
		stack_of_vertices.push_back(u);
	}
	while(sz(stack_of_vertices)>=2){
		vt_tree[stack_of_vertices[sz(stack_of_vertices)-2]].push_back(stack_of_vertices.back());
		stack_of_vertices.pop_back();
	}
	return stack_of_vertices[0];

}
void work(int node,int p=-1){
	//debug() << imie(node) imie(p) imie(vt_tree[node]);
	for(auto el:vt_tree[node]){
		if(el==p) continue;
		work(el,node);
	}
	if(is_important[node]){
		dp[node][1]=0;
		for(auto el:vt_tree[node]){
			if(el!=p) dp[node][1]+=dp[el][0];
		}
		dp[node][0]=dp[node][1]+1;
		return;
	}
	ll sum0=0;
	ll sum1=0;
	ll min_diff=0;
	for(auto el:vt_tree[node]){
		if(el!=p){
			sum0+=dp[el][0];
			sum1+=dp[el][1];
			min_diff=min(min_diff,dp[el][1]-dp[el][0]);
		}
		
	}
	dp[node][0]=min(sum0,sum1+1);
	dp[node][1]=min(sum0+min_diff,dp[node][0]);
}

void solve(){
	cin >>n;
	for(int i=0;i<n-1;i++){
		ll from,to;
		cin >> from >>to;
		from--;
		to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	dfs(0);
	ll q;
	cin >>q;
	for(int i=0;i<q;i++){
		for(auto el:choosenVertices){
			dp[el][0]=0;
			dp[el][1]=0;
			vt_tree[el].clear();
			is_important[el]=false;
		}
		choosenVertices.clear();
		ll k;
		cin >>k;
		for(int j=0;j<k;j++){
			ll v;
			cin >>v;
			v--;
			choosenVertices.push_back(v);
			is_important[v]=true;
			
		}
		// check if there is there is a link between 
		bool whoops=false;
		for(auto el:choosenVertices){
			if(parr[el]!=-1 && is_important[parr[el]]){
				whoops=true;
			}
		}
		if(whoops){
			cout << -1<<'\n';
			continue;
		}
		
		ll root=create_vt_tree();
		work(root);

		//debug() << imie(choosenVertices) imie(dp[root][1]) imie(root) imie(dp[root][0]);
		
		cout << dp[root][1]<<'\n';
	}





}
	
	

 
int main() {
	fastInp;
//	init();
	//debug() << imie(s);
	//freopen("grids.in","r",stdin);
	//freopen("res.out","w",stdout);
	// __gcd <long long> (x, y);
	int tc=1;
	//debug() << imie(sieve);
	//cin >> tc;
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