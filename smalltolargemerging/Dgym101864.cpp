#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

typedef long long ll;
typedef long double ld;
ll n,d;

const ll MOD = 998244353;
ll INF=2e18;

// __builtin_popcount() Function
// problem D here: https://codeforces.com/gym/101864/attachments/download/7365/2018-bacs-contest-replay-en.pdf
// with small to large you can maintain in a datastructure the subtree of a tree
// here we maintenant the alltree-subtree for each node ;) , so we basically mirrored it.
// but for you to visualize it, you can say that in every node after solving everything for all subtree
// you have the big child inserted in the tree (so the values are already added or subtracted depending on the problem)
// and you need to add (or max or everything ..) or substract the values in the other childs
// complexity O(n log2(n)) the extra log is from the datastructure. 
const int N=2e5+5;

ll depth[N];
vector<ll> adj[N];
int sze[N],bchd[N];
vector<int> ve;
int tin[N],tout[N],timer;
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

vector<ll> vec(N);
SegmentTree st(vec);


void dfs(int u,int p=-1){
    tin[u]=++timer;
    ve.push_back(u);
    int mxv=-1;
    int mx=0;
    bchd[u]=-1;
    sze[u]=1;
    if(p!=-1){
        depth[u]=1+depth[p];
    }
    for(auto v:adj[u]){
        if(v==p) continue;
        dfs(v,u);
        sze[u]+=sze[v];
        if(sze[v]>mx){
            mx=sze[v];
            mxv=v;
        }
    }
    bchd[u]=mxv;
    tout[u]=timer;
}

vector<ll> beauty(N);
vector<ll> ans(N);
void solve(int u,bool keep=0,int p=-1){
    for(auto v:adj[u]){
        if(v==p || v==bchd[u]) continue;
        solve(v,0,u);
    }
    if(bchd[u]!=-1){
        solve(bchd[u],1,u);
    }
    // in this area starting from this!!, you have only the big child inserted in the datastructure.
    // do whatever you want now.
    st.update(depth[u],-beauty[u]);
    for(auto v:adj[u]){
        if(v==p || v==bchd[u]) continue;
        for(int i=tin[v];i<=tout[v];i++){
            int x=ve[i];
            st.update(depth[x],-beauty[x]);
        }
    }
    ans[u]=st.RSQ(0,n);
    
    if(!keep){
        for(int i=tin[u];i<=tout[u];i++){
            int ind=ve[i];
            st.update(depth[ind],beauty[ind]);
        }
    }

}


void solve(){
    ve.clear();
    timer=0;
    cin >>n;
    timer=-1;
    for(int i=0;i<=2*n;i++){
        ll gg=st.RSQ(i,i);
        st.update(i,-gg);
        adj[i].clear();
        depth[i]=0;
    }
    for(int i=0;i<n;i++) cin>>beauty[i];
    for(int i=2;i<=n;i++){
        ll v;
        cin >>v;
        v--;
        adj[v].push_back(i-1);
    }
    dfs(0);
    for(int i=0;i<n;i++){
        st.update(depth[i],beauty[i]);
    }
    solve(0);
    for(int i=1;i<n;i++){
        cout << ans[i]<<"\n";
    }
   





}
	
	

 
int main() {
	fastInp;
	int tc=1;
	cin >> tc;
    

	while(tc--){
	
		solve();
		
	}

	return 0;
}
