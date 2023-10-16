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
// problem link: https://codeforces.com/contest/1679/problem/D (I enjoyed this problem)
// this problem is solvable with binary seach + dp on max path in dag. (always think the dag as a prerequisite and not prequisite will need someting that is needing it (so no cycle))
const ll MOD = 998244353;
ll INF=2e18;
vector<pair<ll,ll>> fromto;
vector<ll> vals;
const int NAX=2e5+5;
vector<ll> adjdir[NAX];
vector<ll> toplist;
ll k;
bool visited[(int)2e5 + 5];
vector<ll> dp(NAX,-1e9);
bool t=false;
set<ll> inside;
void dfs(int nn) {
	// this part is to check if tehere is a cycle and it's in n logn we can optimize it in O(n)
	if(t) return;
	debug() << imie(nn);
	visited[nn] =true;
	inside.insert(nn);
	for (int u : adjdir[nn]) {
		if(inside.count(u)) {
			t=true;
			return;
		}
		if(!visited[u]) dfs(u);
	}
	inside.erase(nn);
	

}
void dfs1(ll node){
	
	visited[node]=true;
	for(auto el:adjdir[node]){
		if(!visited[el]){
			dfs1(el);
		}
	}
	toplist.push_back(node);
}
bool check(ll v){
	inside.clear();
	toplist.clear();

	for(int i=0;i<n;i++){
		adjdir[i].clear();
		visited[i]=false;
		dp[i]=-1e9;
		
	}
	debug() << imie(v) imie(vals[1]) imie(vals[0]);
	for(auto el:fromto){
		//debug() << imie(el);
		if(vals[el.first]<=v && vals[el.second]<=v){
			//adjund[el.first].push_back(el.second);
			adjdir[el.first].push_back(el.second);
		//	debug() << imie(el.first) imie(el.second);
			//adjund[el.second].push_back(el.first);
		}
	}
	t=false;
	bool f=false;
	for(int i=0;i<n;i++){
		if(vals[i]<=v&&!visited[i]){
			dfs(i);
			debug() << imie(f) imie(i);
		}
	}
	if(t) return true;
	for(int i=0;i<n;i++){
		visited[i]=false;
	}
	debug() <<imie(f);
	
	debug() << imie(adjdir[5]);
	for(int i=0;i<n;i++){
		if(vals[i]<=v&&!visited[i]){
			dfs1(i);
		}
	}

	debug() << imie(toplist);
	for(auto el:toplist){
		dp[el]=0;
		for(auto ell:adjdir[el]){
			dp[el]=max(dp[el],dp[ell]+1);
		}
	}
	//debug() << imie(dp) imie(v);
	for(int i=0;i<n;i++){
		if(dp[i]>=k) return true;
	}
	return false;



}
void solve(){
	ll m;
	cin >>n >>m >>k;
	k--;
	vals.resize(n);
	for(auto& el:vals) cin>>el;
	for(int i=0;i<m;i++){
		ll from,to;
		cin >>from >>to;
		from--;to--;
		fromto.push_back({from,to});
	}
	ll left=0;
	ll right=2e9;
	bool ok=false;
	//debug() << imie(check(10));
	while(right-left>1){
		ll mid=(right+left)/2;
		if(check(mid)){
			right=mid;
			ok=true;
		}else{
			left=mid;
		}
	}
	if(!ok){
		cout << -1<<'\n';
		return;
	}
	cout << right<<'\n';

	

	


}
	
	

 
int main() {
	fastInp;

	int tc=1;

	while(tc--){
		//i++;
		//cout <<"Test " << i << ":" << "\n";
		
		solve();
		
	}

	return 0;
}



