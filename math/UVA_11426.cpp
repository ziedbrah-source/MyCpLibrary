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
// problem link: https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&category=0&problem=2421&mosmsg=Submission+received+with+ID+29002010
// basically given n, give the sum of all gcd(i,j); i<j; 
// solvable by the phi function
// because supp that d is a divisor of i, then we know that you can get d*phi[i/d]  ( hsebet eli andhom gcd= d el kol bel faza hedhi
// for the proof look at the notes)
const ll MOD = 998244353;
ll INF=2e18;
const int NAX=4e6+5;
ll res[NAX];
vector<int> divs[NAX];
ll phi[NAX];
void init(){
    for(ll i=2;i<NAX;i++) phi[i]=i;
    for(ll i=2;i<NAX;i++){
        if(phi[i]==i){
            for(ll j=i;j<NAX;j+=i){
                phi[j]=(phi[j]/i)*(i-1);
            }
        }
    }
   
    for(int i=1;i<NAX;i++){
        for(int j=i;j<NAX;j+=i){
            //divs[j].push_back(i);
            res[j]+=(phi[j/i]*i);
        }
        
    }
    for(int i=2;i<NAX;i++){
        res[i]+=res[i-1];
    }
    

}

void solve(){

    cout << res[n]<<'\n';
}
    
    

 
int main() {
    fastInp;
    init();
    //debug() << imie(s);
    //freopen("grids.in","r",stdin);
    //freopen("res.out","w",stdout);
    // __gcd <long long> (x, y);
    int tc=1;
    //debug() << imie(sieve);
    //cin >> tc;
    //cout << setprecision(10)<<fixed;

    while(true){
        //i++;
        //cout <<"Test " << i << ":" << "\n";
        cin >>n;
        if(n==0) break;
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


