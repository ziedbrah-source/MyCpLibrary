#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
int n,d;
const ll MOD = 998244353;
ll INF=2e18;
const int NAX=5e3+5;
__int128 dp[NAX][NAX];
// __builtin_popcount() Function
vector<int> adj[NAX];
/*
Géneral Template:
Generally when you want to pick K elements from the subtree of the node v, you use this technique
it goes from n^3 to n^2 
void solve(int v)
{
    Sub[v] = 1;
    dp[v][0] = 1;
    dp[v][1] = 1;

    for(auto u : childrens[v])
    {
       solve(u);

       fill(tmp , tmp + k + 1 , 0);
       for(int i = 1; i <= min(Sub[v] , k); i++)
         for(int j = 0; j <= Sub[u] && i + j <= K; j++)
             tmp[i + j] += dp[v][i] * dp[u][j];

        Sub[v] += Sub[u];

       for(int i = 0; i <= min(K , Sub[v]); i++)
         dp[v][i] = tmp[i];
    }
}



*/
ll tmp[NAX];
int Sub[NAX];
ll szz[NAX];
// combining subtree technique:
// https://open.kattis.com/problems/kthsubtree
// the the n^3 solution is the following:
// in each node, you try to combine the subtrees in this way:
// dp1[i][j]=Sum(0,j) dp1[i-1][j-k]*dp[nodes[i]][k];
// but in order to optimize it; you can do it subtree by subtree..
// and you limit yourself to Sub[node] and Sub[child] 
// now it become n^2
const long long LIMIT = 1e18;
void dfs(int node, int par=-1) {
    Sub[node] = 1;
    vector<ll> tmp(n+2);
    vector<ll> tmp1(n+2);
   
    dp[node][0]=1; // the base case when you have no subtrees.

    for (auto child : adj[node]) {
        if (child == par) continue;
        dfs(child, node);
        for(int i=0;i<=n;i++) tmp[i]=0; // this is where the dp1[j][i] will be stored .
        for(int i=0;i<=Sub[node];i++){ // 
            for(int j=0;j<=Sub[child] && i+j<=n;j++){
                if (dp[node][i] > 0 && dp[child][j] > 0) {
                    if (dp[node][i] > LIMIT / dp[child][j]) {
                        tmp[i + j] += LIMIT; // or set it to LIMIT
                    } else {
                        tmp[i + j] += dp[node][i] * dp[child][j]; // dp[node][i] is actually the dp1[j-1][i]; (the dp of the first i-1 subtrees);
                    }
                } else {
                    tmp[i + j] += dp[node][i] * dp[child][j];
                }


                if (tmp[i + j] > LIMIT) {
                    tmp[i + j] = LIMIT;
                }
            }
        }
     
        Sub[node]+=Sub[child];
        for(int i=0;i<=Sub[node];i++){
            dp[node][i]=tmp[i];
        }
       
        tmp1=tmp; // we don't do this always, this is just because I wanted to get the latest dp values for this node.; it's the as dp[node][i] :)
    }

   
    dp[node][0]=1;
    dp[node][1]=1; // this part it means that I ve took this node (because it's a subgraph)
    
    for(int i=2;i<=n;i++){
        dp[node][i]=tmp1[i-1]; // this is to give the real values to the dp (because I need to pick myself to the combination + me);
    }
   
    for(int i=0;i<=n;i++){
        szz[i]+=dp[node][i]; // this is just to see how many subgraph with size i :)
    }
}

void solve(){
    cin >>n;
    ll k;
    cin >>k;
    for(int i=0;i<n-1;i++){
        int f,t;
        cin >>f >>t;
        f--;t--;
        adj[f].push_back(t);
        adj[t].push_back(f);
    }
    dfs(0);
    
   
    for(int i=1;i<=n;i++){
        if(szz[i]>=k){
            cout << i <<'\n';
            return;
        }
        k-=szz[i];
    }
    cout << -1<<'\n';

}
    
    

 
int main() {
    fastInp;
    int tc=1;
    while(tc--){
        solve();
        
    }

    return 0;
}

