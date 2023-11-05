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

const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
ll m;
vector<ll> vec;
ll A;
ll mini=2e18;
const int N=5e5+10;
int Tree[4*N] , lazy[4*N], upd[4*N], a[N] , v[N];
int n , q ;

void unlazy (int id , int ns , int ne ){
    if (upd[id]==0) return;
    Tree[id]+= lazy[id];
    if (ns==ne){
        lazy[id]= upd[id]=0;
        return;
    }
    int l = 2*id +1 , r = 2*id +2 ;
    lazy[l]+= lazy[id];
    lazy[r] += lazy[id];
    upd[l]= upd[r]=1 ;
    lazy[id]= upd[id]=0;

}

void build (int id = 0,int ns = 1 , int ne = n){
    if (ns == ne ) {Tree[id]= a[ns] ;return;}
    int l = 2*id +1 , r = 2*id +2 , md = ns + (ne-ns)/2 ;
    build (l ,ns , md ) ; build (r , md +1 , ne );
    Tree[id]= max (Tree[r], Tree[l]);
}

int query( int qs , int qe , int id= 0 ,int ns = 1, int ne = n ){
    unlazy (id, ns , ne);
    if (ne<qs || ns > qe) return -INF ;
    if (qs<= ns && ne <= qe) return Tree[id];
    int l = 2*id +1 , r = 2*id +2 , md = ns + (ne-ns)/2 ;
    return max( query(qs , qe, l , ns , md),query(qs , qe, r, md+1 , ne));
}

void update (int qs , int qe  , int val , int id = 0, int ns = 1 , int ne = n ){
    unlazy (id, ns , ne);
    if (ne<qs || ns > qe) return ;
    if (qs<= ns && ne <= qe) {
        lazy[id]+= val ;
        upd[id]=1 ;
        unlazy (id, ns , ne);
        return ;
    }
    int l = 2*id +1 , r = 2*id +2 , md = ns + (ne-ns)/2 ;
    update (qs,qe , val , l , ns , md) ; update (qs , qe , val , r , md+1 , ne);
    Tree[id]= max (Tree[r], Tree[l]);
}
// problem: https://atcoder.jp/contests/abc327/tasks/abc327_f
// add range + max on a range
vector<int> timer[N];
void solve(){
    ll D,W;
    cin >>n;
    cin >>D>>W;
    for(int i=0;i<n;i++){
        ll ti,xi;
        cin >> ti>>xi;
        timer[ti].push_back(xi);
    }
    n=N-4;
    build();
    for(int i=1;i<=D;i++){
        for(auto el:timer[i]){
            update(max(1ll,el-W+1),el,1);
        }
    }

    ll maxi=query(0,n);
    debug() << imie(maxi);
    for(int i=D+1;i<=2e5;i++){
        for(auto el:timer[i-D]){
            update(max(1ll,el-W+1),el,-1);
        }
        for(auto el:timer[i]){
            update(max(1ll,el-W+1),el,1);
        }
        maxi=max(maxi,(ll)query(0,n));
    }

    cout << maxi<<'\n';




   
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


