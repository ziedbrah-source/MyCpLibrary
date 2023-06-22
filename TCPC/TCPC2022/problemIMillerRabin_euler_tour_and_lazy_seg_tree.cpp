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
const int NAX=1e5+5;
vector<int> adj[NAX];
int en[NAX];
int out[NAX];
int timer=0;
vector<ll> euler;
vector<int> val(NAX);
using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n, int iter=5) { // returns true if n is probably prime, else returns false.
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}
void dfs(int node,int par){
	en[node]=timer;
	euler.push_back(val[node]);
	timer++;
	for(auto nd:adj[node] ){
		if(nd==par) continue;
		dfs(nd,node);
	}
	out[node]=timer-1;


}
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
				st[left(index)].update=true;
				st[right(index)].update=true;
				st[left(index)].lazy=st[index].lazy;
				st[right(index)].lazy=st[index].lazy;
				int mid=(l+r)/2;
				st[left(index)].sum= (mid-l+1) * st[index].lazy;
				st[right(index)].sum= (r-mid) * st[index].lazy;
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

		void update(int index,int L,int R,int Lx,int Rx,int v){ // on ajoute v lel range kemel
			propagate(index,L,R); // I m sure eli maandi hata hkeya fou9i fel path edheka mahich updated correctly khater 9a3ed nemchi et ndez fel updates donc impo haja fou9i a9dem meni nsitha..
			
			if(Lx>R || Rx<L) return;

			if(R<=Rx && L>=Lx){
				st[index].update=true;
				st[index].lazy+=v;
				st[index].sum=(R-L+1)*1ll*v;
				
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
				return leftVal+rightVal;

		}

		public:
			LazySegTree(int sz):n(sz),A(n),st(4*n){

			};
			LazySegTree(vector<ll>& initial):LazySegTree((int)initial.size()){
				A=initial;
				build(1,0,n-1);
			}
			void update(int i, int j, int val) { update(1, 0, n-1, i, j, val);}

			ll getSum(int l,int r){
				return getSum(1,0,n-1,l,r);
			}

};
void solve(){
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> val[i];
	}

	for(int i=0;i<n-1;i++){
		int from,to;
		cin>> from >> to;
		from--;
		to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	int q;
	cin >> q;
	dfs(0,-1);
	LazySegTree st(euler);
	debug() << imie(euler) imie(en[6]) imie(out[6]);
	for(int i=0;i<q;i++){
		int ty;
		cin >> ty;
		if(ty==1){
			int nd,val;
			cin >> nd >> val;
			nd--;
			st.update(en[nd],out[nd],val);
		}else{
			int nd;
			cin >> nd;
			nd--;
			ll sum=st.getSum(en[nd],out[nd]);
			debug() << imie(sum);
			if(sum==1){
				cout <<"No"<<"\n";
				continue;
			}
			if(sum==2){
				cout <<"No"<<"\n";
				continue;
			}
			if(sum%2==1){
				if(MillerRabin(sum-2)){
					cout <<"Yes"<<"\n";
				}else{
					cout <<"No"<<"\n";
				}
			}else{
				cout <<"Yes"<<"\n";
			}
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

