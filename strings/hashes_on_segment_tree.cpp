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
#define yes(check) cout << (check ? "Yes" : "No") << endl
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 1e9+7;
// problem : https://atcoder.jp/contests/abc331/tasks/abc331_f
// TLRD; checking if a string is paladinrome b pdate fi point;
// thashi fi weset el seg tree baad tekhou mel 0 lel r;
// aad tna9es mel 0 lel l-1 baad todhreb * inv[poww[l]];
// el hash howa khater sum(A[i]*B^(i))%M;
ll INF=2e18;
static const ll M = 1e9+7;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
static const ll B=prime3;
vector<ll> poww={1};
__int128 mul(ll a, ll b) { return (__int128)a * b; }
ll mod_mul(ll a, ll b) { return mul(a, b) % M; }

void prep(){
	while (poww.size() < 1e6+5) {
			poww.push_back(mod_mul(poww.back(), B));
	}
}
ll inverse(ll x){
    ll res = 1;
    ll b = MOD-2;
    while(b){
        if(b&1) res = (res * x) % MOD;
        x = (x * x) % MOD;
        b >>= 1;
    }
    return res;
}

class SegmentTree{
	private: 
		int n;
		vector<ll> A,st;
	
	int l(int p) {return p<<1;}
	int r(int p) {return (p<<1)+1;}
	
	void build(int p,int L,int R){
		if(L==R){
			st[p]=mod_mul(A[L],poww[L]);
		}else{
			int mid=(R+L)/2;
			build(l(p),L,mid);
			build(r(p),mid+1,R);
			st[p]=(st[l(p)]+st[r(p)])%M;
		}
	}
	void update(int p,int L,int R,int val, int X){
		if(X==R&&L==X){
			st[p]=mod_mul(val,poww[L]);
			return;
		}
		if(R<X || L>X) return;
		int mid=(R+L)/2;
		update(l(p),L,mid,val,X);
		update(r(p),mid+1,R,val,X);
		st[p]=(st[l(p)]+st[r(p)])%M;
	}
	ll RSQ(int p,int L,int R,int LX,int RX){
		if(LX<=L&&R<=RX) return st[p];
		if(R<LX || L>RX) return 0;
		ll currVal=(RSQ(l(p),L,(L+R)/2,LX,RX)+RSQ(r(p),(L+R)/2 +1 ,R,LX,RX))%M;
		return currVal;
	}
	public:
		SegmentTree(int sz) : n(sz), st(4*n) {}
		SegmentTree(const vector<ll> &initialA): SegmentTree((int)initialA.size()){
			A=initialA;
			build(1,0,n-1);
		}
		void update(int X,int val){
			update(1,0,n-1,val,X);
		}
		ll RSQ(int LX,int RX){
			ll v1= RSQ(1,0,n-1,0,RX);
			if(LX!=0){
				v1-=RSQ(1,0,n-1,0,LX-1);
				v1=(v1+M)%M;
				//debug() << imie(LX) imie(poww[LX]) imie(v1);
				v1*=inverse(poww[LX]);
				v1=(v1+M)%M;
			}
			return v1;
		}
		
	
};
void solve(){

	cin >>n;
	cin >>q;
	string s;
	cin >>s;
	vector<ll> vec(n);
	for(int i=0;i<n;i++) vec[i]=s[i];
	
	SegmentTree stt(vec);
	debug() << imie(vec);
	reverse(all(vec));
	SegmentTree sttrev(vec);
	debug() << imie(vec);
	debug() << imie(stt.RSQ(0,1)) imie(sttrev.RSQ(n-2,n-1));
	for(int i=0;i<q;i++){
		int tp;
		cin >> tp;
		if(tp==1){
			int ind;
			char c;
			cin >> ind >>c;
			ind--;
			stt.update(ind,c);
			sttrev.update(n-1-ind,c);

		}else{
			int l,r;
			cin >> l>>r;
			l--;r--;
			ll v=stt.RSQ(l,r);
			ll v1=sttrev.RSQ(n-r-1,n-l-1);
			yes(v==v1);

		}
	}

	
}
	
	

 
int main() {
	fastInp;
	prep();
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


