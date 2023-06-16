// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
// problem : https://codeforces.com/contest/52/problem/C (2200) needing dima el minimum + you need to range add.
struct node {
	ll mini;
	ll lazy;
	bool update;
	node(){
		mini=0;
		lazy=0;
		update=false;
	}

	node(ll _mini,ll _lazy,bool _update){
		mini=_mini;
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
				st[left(index)].update=true;
				st[right(index)].update=true;
				st[left(index)].lazy+=st[index].lazy;
				st[right(index)].lazy+=st[index].lazy;
				int mid=(l+r)/2;
				st[left(index)].mini=st[left(index)].mini+st[index].lazy;
				st[right(index)].mini= st[right(index)].mini+st[index].lazy;
			}
			st[index].lazy=0;
			st[index].update=false;
		}

		node merge(node &l,node &r){
			return node(min(l.mini,r.mini),0,false);
		}

		void build(int index,int L,int R){
			if(L==R){
				st[index].mini=A[L];
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
				st[index].mini+=v;
				
				return;
			}

			int mid=(L+R)/2;
			update(left(index),L,mid,Lx,Rx,v);
			update(right(index),mid+1,R,Lx,Rx,v);
			st[index]=merge(st[left(index)],st[right(index)]);
		}

		ll getMin(int index,int L,int R,int Lx,int Rx){
				propagate(index,L,R);
				if(Lx>R || Rx<L) return INF;
				if(R<=Rx && L>=Lx){
				
				return st[index].mini;
				}		
				int mid=(L+R)/2;
				ll leftVal=getMin(left(index),L,mid,Lx,Rx);
				ll rightVal=getMin(right(index),mid+1,R,Lx,Rx);
				return	min( leftVal,rightVal);

		}

		public:
			LazySegTree(int sz):n(sz),A(n),st(4*n,node(INF,0,false)){

			};
			LazySegTree(vector<ll>& initial):LazySegTree((int)initial.size()){
				A=initial;
				build(1,0,n-1);
			}
			void update(int i, int j, int val) { update(1, 0, n-1, i, j, val);}

			ll getMin(int l,int r){
				return getMin(1,0,n-1,l,r);
			}

};
void solve(){
	cin >> n;
	vector<ll> vec(n);
	for(int i=0;i<n;i++){
		scanf("%lld",&vec[i]);
	}

	LazySegTree st(vec);
	int q;
	scanf("%d",&q);
	for(int i=0;i<q;i++){
		
		ll l,r;
		char c;
		scanf("%lld%lld%c",&l,&r,&c);
		vector<int> v;
			v.push_back(l);
			v.push_back(r);
		if(c=='\n'){

		}else{
			int val;
			cin >> val;
			v.push_back(val);

		}
		if((int)v.size()==2){
			// rmq;
			ll mini=INF;
			if(v[0]<=v[1]){
				mini=st.getMin(v[0],v[1]);
			}else{
				// v[0] > v[1];
				mini=min(st.getMin(0,v[1]),st.getMin(v[0],n-1));
			}
			cout << mini << "\n";
		}else{
			//3 
			int value=v[2];
			if(v[0]<=v[1]){
				st.update(v[0],v[1],value);
			}else{
				// v[0] > v[1];
				st.update(0,v[1],value);
				st.update(v[0],n-1,value);
			}
		}
		
	}
	
}
	
	

 
int main() {
	//fastInp;
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


