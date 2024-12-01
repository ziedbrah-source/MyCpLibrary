#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
// problem : https://cses.fi/problemset/task/1706/ 
// basically the problem is to see whether what subset sums we can get.
// as the sum of components is <=n -> maximum number of disctinct values is sqrt(n)
// => there is a trick for this: constrained knapsack
// => solution is O(sqrt(n)*W) where W is the sum of weights -> it passes! 
// there is another solution with sqrt(n)*W/32 with bitset, but I couldn't get it in my mind, so I have this for now.

const int NAX=1e5+5;
vector<ll> adj[NAX];
bool vis[NAX];
int cnt=0;
void dfs(int node){
    vis[node]=true;
    cnt++;
    for(auto el:adj[node]){
        if(!vis[el]){
            dfs(el);
        }
    }
}
void solve(){
    cin >>n;
    ll m;
    cin >>m;

    for(int i=0;i<m;i++){
        int a,b;
        cin >>a >>b;
        a--;b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> vec;
    for(int i=0;i<n;i++){
        if(!vis[i]){
            cnt=0;
            dfs(i);
            vec.push_back(cnt);
        }
    }
   
    map<ll,ll> mp;
    for(auto el:vec) mp[el]++;
    vector<pair<ll,ll>> sec;
    sec.push_back({0,0});
    // we compress the elemnts to get at max sqrt(n) element!
    for(auto el:mp){
        sec.push_back({el.first,el.second});
    }
  

    vector<vector<int>> dp(sec.size(),vector<int>(n+1,-1));
    dp[0][0]=0;
    vector<bool> ok(n+1);
    /*
        The solution is simple. Let dp[i][j] be the minimum count of ith item 
        that has to be used to get a total cost of j while using some number (possibly 0) of first i items.
        If a total cost of j can not be obtained using first i items, then dp[i][j] =  - 1. 
        The following code is used to calculate dp[i][j],
    */
    for(int i=1;i<sec.size();i++){
        for(int j=0;j<=n;j++){
            if(dp[i-1][j]>=0){
                dp[i][j]=0;
            }else if(j-sec[i].first>=0 && dp[i][j-sec[i].first]>=0 && dp[i][j-sec[i].first]<sec[i].second){
                dp[i][j]=dp[i][j-sec[i].first]+1;
            }else{
                dp[i][j]=-1;
            }
            if(i==sec.size()-1 && dp[i][j]>=0) ok[j]=1;
        }
    }
    for(int i=1;i<=n;i++){
        cout << ok[i];
    }
    

    cout <<'\n';


}
	
	

 
int main() {
	fastInp;
	int tc=1;

	while(tc--){
		solve();
	}
	return 0;
}

