// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
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
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
map<ll,int> ind;
//problem: https://codeforces.com/contest/629/problem/D
// so when you need that the thing that you ll query from behind < than you 
// push the result of its' dp  in the value[j] so when you query behind you next time you are 
// sure that you will query the best thing and that thing is obviously behind you because you inserted it with
// its' value. Gj
class SegmentTree{
	private: 
		int n;
		vector<ll> A,st;
	
	int l(int p) {return p<<1;}
	int r(int p) {return (p<<1)+1;}
	
	void build(int p,int L,int R){
		if(L==R){
			st[p]=A[L];
		}else{
			int mid=(R+L)/2;
			build(l(p),L,mid);
			build(r(p),mid+1,R);
			st[p]=max(st[l(p)],st[r(p)]);
		}
	}
	void update(int p,int L,int R,ll val, int X){
		if(X==R&&L==X){
			st[p]=max(st[p],val);
			return;
		}
		if(R<X || L>X) return;
		int mid=(R+L)/2;
		update(l(p),L,mid,val,X);
		update(r(p),mid+1,R,val,X);
		st[p]=max(st[l(p)],st[r(p)]);
	}
	ll MAXI(int p,int L,int R,int LX,int RX){
		if(LX<=L&&R<=RX) return st[p];
		if(R<LX || L>RX) return 0;
		ll currVal=max(MAXI(l(p),L,(L+R)/2,LX,RX),MAXI(r(p),(L+R)/2 +1 ,R,LX,RX));
		return currVal;
	}
	public:
		SegmentTree(int sz) : n(sz), st(4*n) {}
		SegmentTree(const vector<ll> &initialA): SegmentTree((int)initialA.size()){
			A=initialA;
			build(1,0,n-1);
		}
		void update(int X,ll val){
			update(1,0,n-1,val,X);
		}
		ll MAXI(int LX,int RX){
			return MAXI(1,0,n-1,LX,RX);
		}
		
	
};
void solve(){
	cin >> n ;
	set<ll> s;
	vector<ll> vec(n);
	for(int i=0;i<n;i++){
		
		ll r,h;
		cin >> r >> h;
		//debug() << imie(r) imie(h);
		ll val=r*r*h;
		s.insert(val);
		vec[i]=val;
	}
	//debug() << imie(vec);
	int indd=0;
	for(auto val:s){

		ind[val]=indd;
		indd++;
	}
	debug() << imie("hh");
	vector<ll>A(n+50);
	SegmentTree st(A);
	vector<ll> dp(n+5);
	//debug() << imie(ind);
	for(int i=0;i<n;i++){
		dp[i]=st.MAXI(0,ind[vec[i]]-1)+vec[i];


			st.update(ind[vec[i]],dp[i]);
		

	}
	const ld pi=3.14159265359;
	ld ans=(ld)st.MAXI(0,indd)*pi;
	cout <<ans<< "\n";

	
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
	cout << setprecision(10)<<fixed;

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

