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

const ll MOD = 998244353;
ll INF=2e18;
// submission link: https://atcoder.jp/contests/abc322/submissions/46127290
// based on how much the segment has been touched nice :)
struct node {

	ll lazy; // lazy here means 9adeh ena t'updatit men mara.
	// index 0 is 0 , index 1 is 1;
	ll mx[2];
	ll pref[2];
	ll suff[2];
	ll len;

	bool update;
	node(){
		lazy=0;
		update=false;
		len=0;
		for(int i=0;i<2;i++){
			mx[i]=0;
			pref[i]=0;
			suff[i]=0;
		}
	}

	node(ll v,ll _lazy,bool _update){
		lazy=_lazy;
		update=_update;
		len=1;
		for(int i=0;i<2;i++){
			if(i==v){
				mx[i]=1;
				pref[i]=1;
				suff[i]=1;
			}else{
				mx[i]=0;
				pref[i]=0;
				suff[i]=0;
			}
		}
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
				st[left(index)].update=true;
				st[right(index)].update=true;
				st[left(index)].lazy+=st[index].lazy;
				st[right(index)].lazy+=st[index].lazy;
				ll typright=abs(st[right(index)].lazy-st[index].lazy)%2;
				ll type=st[right(index)].lazy%2;
				ll typleft=abs(st[left(index)].lazy-st[index].lazy)%2;
				ll type1=st[left(index)].lazy%2;
				if(typright!=type){
						flip(st[right(index)]);
				}
				if(typleft!=type1){
					flip(st[left(index)]);
				}
			}
			st[index].lazy=0;
			st[index].update=false;
		}
		void flip(node& l){
			swap(l.mx[0],l.mx[1]);
			swap(l.pref[0],l.pref[1]);
			swap(l.suff[0],l.suff[1]);
		}

		node merge(node &l,node &r){
			node nd;
			for(int i=0;i<2;i++){
				nd.pref[i]=l.pref[i]+(l.pref[i]==l.len?r.pref[i]:0);
				nd.suff[i]=r.suff[i]+(r.suff[i]==r.len?l.suff[i]:0);
				nd.mx[i]=max({r.mx[i],l.mx[i],l.suff[i]+r.pref[i]});

			}
			nd.len=r.len+l.len;
			return nd;
		}

		void build(int index,int L,int R){
			if(L==R){
				st[index]=node(A[L],0,0);
				return;
			}
			int mid=(L+R)/2;
			build(left(index),L,mid);
			build(right(index),mid+1,R);
			st[index]=merge(st[left(index)],st[right(index)]);
		}

		void update(int index,int L,int R,int Lx,int Rx,int v){ // on ajoute v lel range kemel
			propagate(index,L,R); // I m sure eli maandi hata hkeya fou9i fel path edheka mahich updated correctly khater 9a3ed nemchi et ndez fel updates donc impo haja fou9i a9dem meni nsitha..
			
			if(Lx>R || Rx<L) return;

			if(R<=Rx && L>=Lx){
				st[index].update=true;
				st[index].lazy+=v;
				//for(int i=0;i<v;i++){
					flip(st[index]);
				
				
				
				
				return;
			}

			int mid=(L+R)/2;
			update(left(index),L,mid,Lx,Rx,v);
			update(right(index),mid+1,R,Lx,Rx,v);
			st[index]=merge(st[left(index)],st[right(index)]);
		}

		node getSum(int index,int L,int R,int Lx,int Rx){
				propagate(index,L,R);
				if(Lx>R || Rx<L) return node();

				if(R<=Rx && L>=Lx){
				
				return st[index];
				}		
				int mid=(L+R)/2;
				node leftVal=getSum(left(index),L,mid,Lx,Rx);
				node rightVal=getSum(right(index),mid+1,R,Lx,Rx);
				return merge(leftVal,rightVal);

		}

		public:
			LazySegTree(int sz):n(sz),A(n),st(4*n){

			};
			LazySegTree(vector<ll>& initial):LazySegTree((int)initial.size()){
				A=initial;
				build(1,0,n-1);
			}
			void update(int i, int j, int val) { update(1, 0, n-1, i, j, val);}

			node getSum(int l,int r){
				return getSum(1,0,n-1,l,r);
			}

};
void solve(){
	cin >> n>>q;

	string s;
	cin >> s;
	vector<ll> vec(n);
	for(int i=0;i<n;i++){
		vec[i]=s[i]-'0';
	}
	debug() << imie(s);
	
	LazySegTree st(vec);
	node nd=st.getSum(0,n-1);
	for(int i=0;i<q;i++){
		ll type,l,r;
		cin >> type>>l>>r;
		l--;r--;
		if(type==1){
			st.update(l,r,1);
		}else{
			node nd=st.getSum(l,r);
			cout << nd.mx[1]<<'\n';
		}
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


