#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
// great sqrt decomposition on trees idea.
// the compexlity analysis is really cool here;
// for me it' goes like this : if we cut the tree into sqrt
// and we save only the pairs at that level when we will get the query;
// the complexity goes like this: O(n sqrt(n)) for the save and O(q) because at max q queries will touch the saved values;
// + O (Q*sqrt(N)) for the query itself!
// problem: https://codeforces.com/contest/1806/problem/E
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
    size_t operator()(pair<uint64_t,uint64_t> x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
	}
};
unordered_map<pair<ll,ll>,ll,custom_hash> dp;
const int SQRTT=330;
const int NAX=1e5+5;
vector<ll> depth(NAX);
vector<ll> adj[NAX];
vector<ll> par(NAX);
vector<ll> val(NAX);

void dfs(int node,int d){
    depth[node]=d;
    for(auto el:adj[node]){
        dfs(el,d+1);
    }
}
pair<ll,ll> getpair(int u,int v){
    return {min(u,v),max(u,v)};
}
ll query(int u,int v){
    debug() << imie(u) imie(v);
    if(u==0 && v==0) return 0;
    pair<ll,ll> p=getpair(u,v);
    bool tosave=(depth[u]%SQRTT==0);
    // if tosave is important! otherwise the complexity will grow
    if(tosave && dp.count(p)){
        return dp[p];
    }
   
    ll vv=val[u]*val[v]+query(par[u],par[v]);


    if(tosave){
       
        dp[p]=vv;
    }
    return vv;

}
void solve(){
    cin >>n;
    cin >>q;
    for(int i=1;i<=n;i++) cin>>val[i];
    for(int i=2;i<=n;i++){
        ll parr;
        cin >>parr;
        adj[parr].push_back(i);
        par[i]=parr;
    }
    dfs(1,0);
    for(int i=0;i<q;i++){
        ll u,v;
        cin >>u >>v;
        cout << query(u,v)<<'\n';
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




