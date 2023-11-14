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
// dp[i][j][1] is the maximum number of segments that I can take that are inside the segment i,j
// it's ofc (dp[i+1][j]) or dp[i][j-1] or for each element starting at i, 1+dp[i][el][true]+dp[el+1][r][false];
short dp[6005][6005][2];
// problem : https://codeforces.com/contest/1399/problem/F rating 2300 DP.
vector<short> startingAt[6005];
ll go(int l,int r,bool ok){
    if(l>r) return 0;
    if(dp[l][r][ok]!=-1) return dp[l][r][ok];
    ll maxi=go(l+1,r,false);
    maxi=max(maxi,go(l,r-1,false));
    for(auto el:startingAt[l]){
        if(el<=r){
            if(ok && el==r) continue;
            maxi=max(maxi,1+go(l,el,true)+go(el+1,r,false));
        }
    }
    return dp[l][r][ok]=maxi;
}
void solve(){
    cin >>n;
    for(int i=0;i<2*n+5;i++) startingAt[i].clear();

    for(int i=0;i<2*n+5;i++){
        for(int j=0;j<2*n+5;j++){
            dp[i][j][0]=-1;
            dp[i][j][1]=-1;
        }
    }
    set<ll> st;
    vector<pair<ll,ll>> vec(n);
    for(int i=0;i<n;i++){
        ll a,b;
        cin >> a>>b;
        st.insert(a);
        st.insert(b);
        vec[i]={a,b};
    }
    map<ll,ll> mp;
    int ind=1;
    for(auto el:st){
        mp[el]=ind;
        ind++;
    }
    for(int i=0;i<n;i++){
        startingAt[mp[vec[i].first]].push_back(mp[vec[i].second]);
    }
    cout << go(1,ind,false)<<'\n';
}
    
    

 
int main() {
    fastInp;
    int tc=1;
    //debug() << imie(sieve);
    cin >> tc;

    while(tc--){
        solve();
    }

    return 0;
}



