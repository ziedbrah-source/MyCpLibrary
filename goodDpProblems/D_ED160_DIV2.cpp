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
// link : https://codeforces.com/contest/1913/problem/D
// it's an normal dp problem wwith a monotonic style optimization.
// it can be done with monotonic queue tho.
const ll MOD = 998244353;
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
			st[p]=min(st[l(p)],st[r(p)]);
		}
	}
	ll RSQ(int p,int L,int R,int LX,int RX){
		if(LX<=L&&R<=RX) return st[p];
		if(R<LX || L>RX) return 2e18;
		ll currVal=min(RSQ(l(p),L,(L+R)/2,LX,RX),RSQ(r(p),(L+R)/2 +1 ,R,LX,RX));
		return currVal;
	}
	public:
		SegmentTree(int sz) : n(sz), st(4*n) {}
		SegmentTree(const vector<ll> &initialA): SegmentTree((int)initialA.size()){
			A=initialA;
			build(1,0,n-1);
		}
		ll RSQ(int LX,int RX){
			return RSQ(1,0,n-1,LX,RX);
		}
		
	
};
struct node {
	ll sum;
	ll lazy;
	bool update;
	node(){
		sum=0;
		lazy=0;
		update=false;
	}

	node(ll _sum,ll _lazy,bool _update){
		sum=_sum;
		lazy=_lazy;
		update=_update;
	}
};

class LazySegTree{
	private:
		int n;
		vector<ll> A;
		vector<node> st;
		int left(int index) {return 2*index;}
		int right(int index) {return 2*index+1;}
		void propagate(int index,int l,int r){
			if(!st[index].update) return;
			if(l!=r){
				st[index].lazy%=MOD;
				st[index].sum%=MOD;
				st[left(index)].update=true;
				st[right(index)].update=true;
				st[left(index)].lazy+=st[index].lazy;
				st[left(index)].lazy%=MOD;
				st[right(index)].lazy+=st[index].lazy;
				st[right(index)].lazy%=MOD;
				int mid=(l+r)/2;
				st[left(index)].sum+= (mid-l+1) * st[index].lazy;
				st[right(index)].sum+= (r-mid) * st[index].lazy;
				st[left(index)].sum%=MOD;
				st[right(index)].sum%=MOD;

			}
			st[index].lazy=0;
			st[index].update=false;
		}

		node merge(node &l,node &r){
			return node(l.sum+r.sum,0,false);
		}

		void build(int index,int L,int R){
			if(L==R){
				st[index].sum=A[L];
				return;
			}
			int mid=(L+R)/2;
			build(left(index),L,mid);
			build(right(index),mid+1,R);
			st[index]=merge(st[left(index)],st[right(index)]);
		}

		void update(int index,int L,int R,int Lx,int Rx,ll v){ // on ajoute v lel range kemel
			propagate(index,L,R); // I m sure eli maandi hata hkeya fou9i fel path edheka mahich updated correctly khater 9a3ed nemchi et ndez fel updates donc impo haja fou9i a9dem meni nsitha..
			
			if(Lx>R || Rx<L) return;

			if(R<=Rx && L>=Lx){
				st[index].update=true;
				st[index].lazy+=v;
				st[index].lazy%=MOD;
				st[index].sum+=(R-L+1)*1ll*v;
				st[index].sum%=MOD;
				
				return;
			}

			int mid=(L+R)/2;
			update(left(index),L,mid,Lx,Rx,v);
			update(right(index),mid+1,R,Lx,Rx,v);
			st[index]=merge(st[left(index)],st[right(index)]);
		}

		ll getSum(int index,int L,int R,int Lx,int Rx){
				propagate(index,L,R);
				if(Lx>R || Rx<L) return 0;

				if(R<=Rx && L>=Lx){
				
				return st[index].sum;
				}		
				int mid=(L+R)/2;
				ll leftVal=getSum(left(index),L,mid,Lx,Rx);
				ll rightVal=getSum(right(index),mid+1,R,Lx,Rx);
				return (leftVal+rightVal)%MOD;

		}

		public:
			LazySegTree(int sz):n(sz),A(n),st(4*n){

			};
			LazySegTree(vector<ll>& initial):LazySegTree((int)initial.size()){
				A=initial;
				build(1,0,n-1);
			}
			void update(int i, int j, ll val) { update(1, 0, n-1, i, j, val);}

			ll getSum(int l,int r){
				return getSum(1,0,n-1,l,r);
			}

};
void solve(){
	cin >>n;
	vector<ll> vec(n+1);vec[0]=0;
	for(int i=1;i<=n;i++){
		cin >>vec[i];
	}
	SegmentTree st(vec);
	vector<ll> dp(n+1);
	LazySegTree stt(dp);
	
	ll sum=0;
	for(int i=1;i<=n;i++){
		
		ll mini=vec[i];
		ll l=0;
		ll r=i;
		while(r-l>1){
			ll mid=(r+l)/2;
			if(mini==st.RSQ(mid,i)){
				r=mid;
				debug() << imie(mid) imie(st.RSQ(mid,i));
			}else{
				l=mid;
			}

		}
		debug() << imie(r) imie(i) imie(stt.getSum(r,i));
		stt.update(i,i,(r==1));
		if(r<i){
					ll range=stt.getSum(r,i-1)%MOD;
				stt.update(i,i,range);
		}
		 l=i;
		 r=n+1;
		while(r-l>1){
			ll mid=(r+l)/2;
			if(mini==st.RSQ(i,mid)){
				l=mid;
			}else{
				r=mid;
			}
		}
		
		debug() <<imie(l) imie(stt.getSum(i,i)) imie(i);
		if(l==i) continue;
		stt.update(i+1,l,stt.getSum(i,i));
		
		/*for(int j=i-1;j>=0;j--){
			mini=min(mini,vec[j]);
			if((mini==vec[j]||mini==vec[i])){
				dp[i]+=dp[j];
				dp[i]%=MOD;
			}
		}*/
		/*if(mini==vec[i]) dp[i]++;
		dp[i]%=MOD;
		if(vv==vec[i]) sum+=dp[i];
		sum%=MOD;*/
	}
	for(int i=1;i<=n;i++){
		debug() << imie(i) imie(stt.getSum(i,i));
		if(st.RSQ(i,n)==vec[i]){
			sum+=stt.getSum(i,i);
			sum%=MOD;
		}
	}
	cout <<sum<<'\n';

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
	cin >> tc;
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


