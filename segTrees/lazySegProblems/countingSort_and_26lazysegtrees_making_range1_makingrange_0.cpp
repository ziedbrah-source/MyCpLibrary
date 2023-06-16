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
// 26 lazy seg trees , each for each char in the alphaet , and kinda used counting sort :D 
// problem link : https://codeforces.com/contest/558/problem/E  (2300);
ll INF=2e18;
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
		int charRes;
		vector<ll> A;
		vector<node> st;
		int left(int index) {return 2*index;}
		int right(int index) {return 2*index+1;}
		void propagate(int index,int l,int r){
			if(!st[index].update) return;
			if(l!=r){
				st[left(index)].update=true;
				st[right(index)].update=true;
				int mid=(l+r)/2;
				st[left(index)].sum= (mid-l+1)*st[index].lazy;
				st[right(index)].sum= (r-mid)*st[index].lazy;
				st[left(index)].lazy=st[index].lazy;
				st[right(index)].lazy=st[index].lazy;

			}
			st[index].update=false;
		}

		node merge(node &l,node &r){
			return node(l.sum+r.sum,0,false);
		}

		void build(int index,int L,int R){
			if(L==R){
				int val=0;
				if(A[L]==charRes) val=1;
				st[index].sum=val;
				return;
			}
			int mid=(L+R)/2;
			build(left(index),L,mid);
			build(right(index),mid+1,R);
			st[index]=merge(st[left(index)],st[right(index)]);
		}

		void update(int index,int L,int R,int Lx,int Rx){ // on ajoute v lel range kemel
			propagate(index,L,R); // I m sure eli maandi hata hkeya fou9i fel path edheka mahich updated correctly khater 9a3ed nemchi et ndez fel updates donc impo haja fou9i a9dem meni nsitha..
			
			if(Lx>R || Rx<L) return;

			if(R<=Rx && L>=Lx){
				st[index].update=true;
				st[index].sum=(R-L+1);
				st[index].lazy=1;
				
				return;
			}

			int mid=(L+R)/2;
			update(left(index),L,mid,Lx,Rx);
			update(right(index),mid+1,R,Lx,Rx);
			st[index]=merge(st[left(index)],st[right(index)]);
		}

		
		void deletequery(int index,int L,int R,int Lx,int Rx){ // on ajoute v lel range kemel
			propagate(index,L,R); // I m sure eli maandi hata hkeya fou9i fel path edheka mahich updated correctly khater 9a3ed nemchi et ndez fel updates donc impo haja fou9i a9dem meni nsitha..
			
			if(Lx>R || Rx<L) return;

			if(R<=Rx && L>=Lx){
				st[index].update=true;
				st[index].sum=0;
				st[index].lazy=0;
				return;
			}

			int mid=(L+R)/2;
			deletequery(left(index),L,mid,Lx,Rx);
			deletequery(right(index),mid+1,R,Lx,Rx);
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
				return leftVal+rightVal;

		}

		public:
			LazySegTree(int sz):n(sz),A(n),st(4*n){

			};
			LazySegTree(vector<ll>& initial,int charres):LazySegTree((int)initial.size()){
				A=initial;
				charRes=charres;
				build(1,0,n-1);
			}
			void update(int i, int j) { update(1, 0, n-1, i, j);}
			void deletequery(int i,int j){
				deletequery(1, 0, n-1, i, j);
			}

			ll getSum(int l,int r){
				return getSum(1,0,n-1,l,r);
			}

};
vector<LazySegTree> vec;
void solve(){
	cin >> n >> q;
	string s;
	cin >>s;
	vector<ll> v(n);
	for(int i=0;i<n;i++){
		v[i]=s[i]-'a';
	}

	for(int i=0;i<26;i++){
		LazySegTree st(v,i);
		vec.push_back(st);
	}
	debug() << imie("here");
	for(int i=0;i<q;i++){
		int l,r, k;
		cin >> l  >> r >> k;
		l--;r--;
		vector<ll> occ(26);
		for(int j=0;j<26;j++){
			occ[j]=vec[j].getSum(l,r);
			vec[j].deletequery(l,r);
		}
		int starting=l;
		if(k==1){ // increasing.
			for(int j=0;j<26;j++){
				vec[j].update(starting,starting+occ[j]-1);
				starting=starting+occ[j];
			}
		}else{
			for(int j=25;j>=0;j--){
				vec[j].update(starting,starting+occ[j]-1);
				starting=starting+occ[j];
			}			
		}

		
	}

	for(int i=0;i<n;i++){
		for(int j=0;j<26;j++){
			if(vec[j].getSum(i,i)){
				cout << char(j+'a');
				continue;
			}
		}
	}
	cout <<"\n";

	
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


