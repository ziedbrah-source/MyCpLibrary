#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,d;

// https://codeforces.com/contest/1009/problem/F small to large + walk on segment tree.
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
	void update(int p,int L,int R,int val, int X){
		if(X==R&&L==X){
			st[p]+=val;
			return;
		}
		if(R<X || L>X) return;
		int mid=(R+L)/2;
		update(l(p),L,mid,val,X);
		update(r(p),mid+1,R,val,X);
		st[p]=max(st[l(p)],st[r(p)]);
	}
	ll RSQ(int p,int L,int R,int LX,int RX){
		if(LX<=L&&R<=RX) return st[p];
		if(R<LX || L>RX) return 0;
		ll currVal=max(RSQ(l(p),L,(L+R)/2,LX,RX),RSQ(r(p),(L+R)/2 +1 ,R,LX,RX));
		return currVal;
	}

    ll walk_on_tree(int p,int L,int R,int LX,int RX,ll value){
       
		if(R==L) return L;
        ll mid=(L+R)/2;
        if(st[l(p)]>=value){
            return walk_on_tree(l(p),L,(L+R)/2,LX,RX,value);
        }
        return walk_on_tree(r(p),(L+R)/2 +1 ,R,LX,RX,value);
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

        ll walk_on_tree( int LX,int RX,ll value){
            return walk_on_tree(1,0,n-1,LX,RX,value);
        }
		
	
};

const int N = 1e6 + 5;

int a[N], q;
int u, v;
vector<int> adj[N];
int sze[N], bchd[N];
int tin[N], tout[N], timer;
vector<int> ve;
int depth[N];
vector<ll> vec(N);

SegmentTree st(vec);
void dfs(int u, int p = -1) {
    tin[u] = ++timer;
    ve.push_back(u);
    int mxv = -1;
    int mx = 0;
    bchd[u] = -1;
    sze[u] = 1;
    if(p!=-1){
        depth[u]=1+depth[p];
    }
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sze[u] += sze[v];
        if (sze[v] > mx) {
            mx = sze[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = timer;
}
int resp[N];
void solve(int u, bool keep = 0, int p = -1) {
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        solve(v, 0, u);
    }
    if (bchd[u] != -1) {
        solve(bchd[u], 1, u);
    }
    st.update(depth[u],1);

    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            int x = ve[i];

            st.update(depth[x],1);
        }
    }
    int l=depth[u];
    int r=N-1;
    ll maxi=st.RSQ(l,N-1);
    debug() << imie(maxi) imie(u) imie(keep) imie(l);
    if(maxi==1){
        
        
    }else{
        ll value=st.walk_on_tree(1,N-1,maxi);
         resp[u]=value-depth[u];
    }
   
    if (!keep) {
        for(int i=tin[u];i<=tout[u];i++){
            int ind=ve[i];
            st.update(depth[ind],-1);
            debug() << imie(u) imie(ind);
        }
    }
}

void test_case() {
    ve.clear();
    timer = -1;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        --u;
        --v;
        
        adj[u].push_back(v);
        adj[v].push_back(u);
        debug() << imie(i) imie(u) imie(v);
    }
      debug() << imie("HNE");
    dfs(0);
   
    solve(0);
    for(int i=0;i<n;i++){
        cout << resp[i]<<'\n';
    }
    
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
