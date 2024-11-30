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
int n,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
// problem link: https://www.codechef.com/problems/CHEFEXQ?tab=statement 
// sqrt decomposition problem: the idea is to always make sure that el blocks eli fel weset t'updati alehom lazy [kel haja el global alih el kol]
// and fel chtar el blocks ymin w ysar , t'updatehom el kol b façon mouaayna w tepropagi el lazy w traj3ou lel 0.
// play with el blocksize ;)

// block id starts from 0
// block_start(0)=1; // it's 1 based
// block_end(0) gives you block_size+1 -> for loop < not <=
// read in 1 based !
// Gj :)

constexpr int MAXA = 3e6 + 10;
constexpr int MAXN=1e5+10;
constexpr int BLOCK_SIZE = 1200;

inline int block_start(int id) { return id * BLOCK_SIZE + 1; }
inline int block_end(int id) { return min((id + 1) * BLOCK_SIZE, n) + 1; }
inline int block_id(int x) { return (x - 1) / BLOCK_SIZE; }

struct {
    int occ[MAXN / BLOCK_SIZE + 10][MAXA];
    int arr[MAXN]; // the prefxor;
    int value[MAXN]; // the values;
    int lazy[MAXN/BLOCK_SIZE+10];   
    int blocks=MAXN/BLOCK_SIZE+10;
    void read(){
        for(int i=1;i<=n;i++){
            cin >>value[i];
          
            arr[i]^=(value[i]^arr[i-1]);
            occ[block_id(i)][arr[i]]++;
          
        }
    }
    void deb(){
        for(int i=1;i<=n;i++){
            debug() << imie(i) imie(value[i]) imie(lazy[i]) imie(arr[i]);
        }
    }
    void update(int pt, int c){
        int id=block_id(pt);
        int start=block_start(id);
        int endd=block_end(id);
        int was=value[pt];
        value[pt]=c;
        for(int i=start;i<endd;i++){
            occ[id][arr[i]]--;
            if(i==pt){
                occ[id][arr[i]^was^lazy[id]^c]++;
               arr[i]=arr[i]^was^lazy[id]^c;
                continue;
            }
            if(i>pt){
                occ[id][arr[i]^lazy[id]^c^was]++;
                arr[i]=arr[i]^lazy[id]^c^was;
                continue;
            }
            occ[id][arr[i]^lazy[id]]++;
            arr[i]=arr[i]^lazy[id];

        }
        lazy[id]=0;
        for(int i=id+1;i<=block_id(n);i++){
            lazy[i]=lazy[i]^was;
            lazy[i]^=c;
        }
    }
    ll query(int pt,int k){
        int id=block_id(pt);
        int start=block_start(id);
        debug() << imie(id) imie(pt) imie(k) imie(start);
        ll sum=0;
        for(int i=0;i<id;i++){
            int lz=lazy[i];
            sum+=occ[i][lz^k];
        }
        for(int i=start;i<=pt;i++){ 
            int lz=lazy[id];
            int needed=lz^k;
            if(arr[i]==needed) sum++;
        }
        return sum;

    }

} sq;
void solve(){
    cin >>n;
    int q;
    cin >>q;
    sq.read();
    for(int i=0;i<q;i++){
        int a,b,c;
        cin >>a >>b >> c;
        if(a==1){
            sq.update(b,c);
        }else{
            cout << sq.query(b,c)<<'\n';
        }
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
