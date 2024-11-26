#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
#define all(x)            (x).begin(),(x).end()
typedef long long ll;
typedef long double ld;
ll n,d;


const ll MOD = 998244353;
ll INF=2e18;

// problem: https://codeforces.com/gym/100589/problem/A 
// doing sq on queries .. complexity is O(sqrt(Q)*Q*log(n)+sqrt(Q)*N);
// basically updating the tree at every sqrt and responding to queries with the persistet changes + the last sqrt(Q) updates check 
// => classic sq on queries.
const int NAX=1e5+5;
ll dp[NAX];
ll new_dp[NAX];
ll newvals[NAX];
vector<ll> adj[NAX];
ll m;
ll en[NAX];
ll st[NAX];
int timer=0;
int sq=300;
int dep[NAX];
vector<ll> values[NAX];
void dfs(int node,int par=-1){
    
    st[node]=timer;
    timer++;
    values[dep[node]].push_back(timer-1);
    for(auto el:adj[node]){
        if(el==par) continue;
        dep[el]=dep[node]+1;
        dfs(el,node);
    }

   
    en[node]=timer-1;
}
void dfs1(int node,int par=-1){
    
   
    new_dp[node]+=newvals[dep[node]];
    for(auto el:adj[node]){
        if(el==par) continue;
        dfs1(el,node);
        new_dp[node]+=new_dp[el];
    }
    dp[node]+=new_dp[node];
   
}
void solve(){

    cin >>n;
    cin >>m;

    for(int i=0;i<n-1;i++){
        ll from,to;
        cin >>from >>to;
        from--;to--;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    dfs(0);
    vector<pair<ll,ll>> queries;
    for(int i=1;i<=m;i++){
        if(i%sq==0){
            // dfs1
            dfs1(0);
            // remove the last block updates.
            for(int j=0;j<=n;j++){
                newvals[j]=0;
                new_dp[j]=0;
            }
            queries.clear();
            
        }
        ll t;
        cin >>t;
        if(t==1){
            ll l,y;
            cin >>l >>y;
            queries.push_back({l,y});
            newvals[l]+=y;
        }else{
            ll x;
            cin >>x;
            x--;
            ll curr=dp[x];
            int ss=st[x];
            int endd=en[x];
            for(auto el:queries){
                ll l=el.first;
                ll szz=upper_bound(all(values[l]),endd)-lower_bound(all(values[l]),ss); // this is to see how many nodes with depth X and it's in the subtree of X.
                curr+=szz*el.second;

            }
            cout << curr <<'\n';
        }
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

/*
   Some insights:
    .Binary search
    .Graph representation
    .Write brute force code
    .Change your approach
 
 
 */
