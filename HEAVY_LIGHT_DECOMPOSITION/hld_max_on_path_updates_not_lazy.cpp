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
const int NAX=2e5+5;
vector<int> adj[NAX];
vector<int> values(NAX);
// problem : https://cses.fi/problemset/task/2134/ 
int parent[NAX],heavy[NAX],pos[NAX],head[NAX],depth[NAX];
class MaxSegTree{
	private:
		int n;
		vector<int> A,st;
		int l(int p) {return 2*p;};
		int r(int p) {return 2*p+1;};
		void build(int node,int L,int R){
			if(L==R){
				st[node]=A[L];
				return;
			}
			int mid=(L+R)/2;
			build(l(node),L,mid);
			build(r(node),mid+1,R);
			st[node]=max(st[l(node)],st[r(node)]);
		}

		void update(int node,int L,int R,int Lx,int Rx,int val){
			if(R<Lx || L>Rx) return;
		
			if(L==Lx && Rx==R){
				st[node]=val;
				return;
			}
			int mid=(L+R)/2;
			update(l(node),L,mid,Lx,Rx,val);
			update(r(node),mid+1,R,Lx,Rx,val);
			st[node]=max(st[l(node)],st[r(node)]);

		}
		int getMax(int node,int L,int R,int Lx,int Rx){
			//debug() << imie(node) imie(L) imie(R) imie(Lx) imie(Rx);
			if(L>=Lx && R<=Rx){
				return st[node];
			}
			if(R<Lx || L>Rx) return 0;
				


			int mid=(L+R)/2;
			int maxi1=getMax(l(node),L,mid,Lx,Rx);
			int maxi2=getMax(r(node),mid+1,R,Lx,Rx);
			return max(maxi1,maxi2);
		

		}
		public:
			void build(vector<int>& initial){
				n=(int)initial.size();
				A.resize(n);
				st.resize(4*n);
				A=initial;


				build(1,0,n-1);
			}
			void update(int Lx,int Rx,int val){
				update(1,0,n-1,Lx,Rx,val);
			}

			int getMax(int Lx,int Rx){
				return getMax(1,0,n-1,Lx,Rx);
			}


};
int dfs(int node,int par){
	int sz=1;
	int maxSz=0;
	heavy[node]=-1;
	for(auto el:adj[node]){
		if(el==par) continue;
		parent[el]=node;
		depth[el]=depth[node]+1;
		int szsub=dfs(el,node);
		sz+=szsub;
		if(szsub>maxSz){
			maxSz=szsub;
			heavy[node]=el;
		}
	}
	return sz;
}
int pos_int=0;
void decompose(int node,int v){	
	head[node]=v;
	pos[node]=pos_int++;

	if(heavy[node]!=-1){
		decompose(heavy[node],v);
	}
	for(auto el:adj[node]){
		if(el==parent[node]|| el==heavy[node]) continue;
		decompose(el,el);
	}
}
void init(){
	dfs(0,-1);
	decompose(0,0);

}	
MaxSegTree st;

int query(int a,int b){
	int res=0;
	while(head[a]!=head[b]){
		if(depth[head[a]]<depth[head[b]]){
			swap(a,b);
		}
		int resmax=st.getMax(pos[head[a]],pos[a]);
		//debug() << imie(a) imie(head[a]) imie(b) imie(head[b]);
		res=max(res,resmax);
		a=parent[head[a]];
	}
	if(depth[a]>depth[b]){
		swap(a,b);
	}
	res=max(res,st.getMax(pos[a],pos[b]));
	return res;
}

void update(int a,int val){
	//debug() << imie(a) imie(pos[a]) imie(val);
	st.update(pos[a],pos[a],val);
	//debug() << imie(st.getMax(pos[a],pos[a]));
}	
void solve(){
	int q;
	cin >> n >> q;
	
	for(int i=0;i<n;i++){
		cin >> values[i];
	}

	for(int i=0;i<n-1;i++){
		int from,to;
		cin >> from >> to;
		from--;to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	vector<int> A(n);
	init();
	for(int i=0;i<n;i++){
		A[pos[i]]=values[i];
	}
	st.build(A);
	for(int i=0;i<q;i++){
		int ty;
		cin >> ty;
		if(ty==1){
			int nd,val;
			cin >> nd >>val;
			nd--;
			update(nd,val);
		}else{
			int nd1,nd2;
			cin >> nd1 >> nd2;
			nd1--;nd2--;
			cout <<query(nd1,nd2) << "\n";
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

