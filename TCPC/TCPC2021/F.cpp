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
// mo + seg tree.
ll INF=2e18;
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
			st[p]=st[l(p)]^st[r(p)];
		}
	}
	void update(int p,int L,int R,int val, int X){
		if(X==R&&L==X){
			st[p]=val;
			return;
		}
		if(R<X || L>X) return;
		int mid=(R+L)/2;
		update(l(p),L,mid,val,X);
		update(r(p),mid+1,R,val,X);
		st[p]=st[l(p)]^st[r(p)];
	}
	ll RSQ(int p,int L,int R,int LX,int RX){
		if(LX<=L&&R<=RX) return st[p];
		if(R<LX || L>RX) return 0;
		ll currVal=RSQ(l(p),L,(L+R)/2,LX,RX)^RSQ(r(p),(L+R)/2 +1 ,R,LX,RX);
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
			return RSQ(1,0,n-1,LX,RX);
		}
		
	
};
const int NAX=2e6+5;
vector<ll> vec(NAX);
SegmentTree st(vec);
int id[NAX];
int L[NAX];
int R[NAX];
int l,r;
int ans[NAX];
vector<int> v;
void add(int val){
	ll v=st.RSQ(val,val);
	st.update(val,v+1);
}

void remove(int val){
	ll v=st.RSQ(val,val);
	st.update(val,v-1);
	
}
void update(int index){
	
	while(r<R[index]){
		r++;
		add(vec[r]);
	}
	while(l>L[index]){
		l--;
		add(vec[l]);
	}
	while(r>R[index]){
		remove(vec[r]);
		r--;
	}
	
	while(l<L[index]){
		remove(vec[l]);
		l++;
	}
	
}
int LeftRange[NAX];
int RightRange[NAX];

void mo(){
	
	int B=sqrt(NAX);
	sort(id,id+q,[B](int a,int b){
		
		pair<int,int> p1={L[a]/B,R[a]};
		pair<int,int> p2={L[b]/B,R[b]};
		return p1<p2;
	});
	l=0;
	r=-1;
	for(int i=0;i<q;i++){
		update(id[i]);
		ans[id[i]]=st.RSQ(LeftRange[id[i]],RightRange[id[i]]);
	}
	
	
}
void solve(){
	cin >> n;
	v.resize(n);
	cin >> q;
	for(int i=0;i<n;i++){
		cin >> vec[i];
	}

	for(int i=0;i<q;i++){
		cin >> L[i] >> R[i];
		L[i]--;
		R[i]--;
		cin >> LeftRange[i];
		cin >> RightRange[i];


		id[i]=i;
	}
	mo();
	for(int i=0;i<q;i++){
		cout <<ans[i] << "\n";
	}

	
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

