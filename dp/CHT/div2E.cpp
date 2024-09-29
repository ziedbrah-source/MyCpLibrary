#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
int n,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=3e18+5;

// problem: https://codeforces.com/contest/631/problem/E
// tabda el dp tetkteb haka: dp[i]=max/min(dp[j]+(haja mel i)*(haja mel j)+some constants from j + someconstajts from i)
// w enti t'inseri fel CHT el slope (haja mel j), wel constants howa dp[j]+someconstants from j w abad just hawka line et boooooom , tjib el max/min stuff fi log(n)

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
        if(empty()){
            // if maxi is needed but we can get negative values (else just insert (0,0) from the start if we can't get negative values)
            // if we need mini, I think we always put this if we really need to get a line otherwise we insert just (0,0)
            return -INF;
        }
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};
/*
this is a maxiumum cht but if we need a min one we do this: 
//declaring the max convex hull
LineContainer cht;

//adding a line with slope m and constant c
cht.add(-m, -c);

//querying min value at x
int ans = -cht.query(x);

*/

LineContainer cht;
LineContainer cht2;
const int NAX=2e5+5;
ll counter[NAX];
ll pref[NAX];
ll dp[NAX];
void solve(){
    for(int i=0;i<NAX;i++) dp[i]=-INF;
    
    cin >>n;
    vector<ll> vec(n+7);
    for(ll i=1;i<=n;i++){
        int v;
        cin >>v;
        vec[i]=v;
        counter[i]+=(vec[i]*i);
        pref[i]+=vec[i];
        counter[i]+=counter[i-1];
        pref[i]+=pref[i-1];
       
        
    }
    ll maxi=counter[n];
    for(ll i=1;i<=n;i++){
        // 
        ll value=counter[n]-pref[i];
        
            dp[i]=max(dp[i],value+cht.query(i));
            maxi=max(maxi,dp[i]);
        
        cht.add(vec[i],-vec[i]*i+pref[i]);

        
        
    }
    for(ll i=n;i>=0;i--){
        // 
        ll value=counter[n]-pref[i];
        if(i<=n){
          
          
            dp[i]=max(dp[i],value+cht2.query(i+1));
            maxi=max(maxi,dp[i]);
        }

       ll valuee=0;
       if(i) valuee=pref[i-1];
        
        cht2.add(vec[i],-vec[i]*1LL*i+valuee);

        
    }
    long long mm=maxi;
    cout << mm <<'\n';




}
	
	

 
int main() {
	fastInp;

	int tc=1;

	while(tc--){
		solve();
	}
	return 0;
}
