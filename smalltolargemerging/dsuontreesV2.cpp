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
// DSU ON TREE
// https://codeforces.com/contest/600/problem/E
// TLDR: you need to get the sum of distinct colors that are dominant for every subtree
// do DSU on tree with a map or seg tree OR ANY OTHER DS
// when there is a query on subtree think of this and the online (just euler tour and seg tree lazy or nah.)
// this is version 2 the other version needs a ds for every node 
const ll MOD = 998244353;
ll INF=2e18;
const int NAX=1e5+5;
ll sum[NAX];
vector<ll> A(NAX);
class SegmentTree{
	private: 
		int n;
		vector<ll> A,st;
	
	int l(int p) {return p<<1;}
	int r(int p) {return (p<<1)+1;}
	int merge(ll val,ll val2){
		return max(val,val2);
	}
	void build(int p,int L,int R){
		if(L==R){
			st[p]=0;
		}else{
			int mid=(R+L)/2;
			build(l(p),L,mid);
			build(r(p),mid+1,R);
			st[p]=st[l(p)]+st[r(p)];
		}
	}
	void update(int p,int L,int R,ll val, ll X){
	
		if(X==R&&L==X){
			A[X]+=val;
			if(A[X]>0){
				st[p]=L;
			}else{
				st[p]=0;
			}
				
			return;
		}
		if(R<X || L>X) return;
		int mid=(R+L)/2;
		update(l(p),L,mid,val,X);
		update(r(p),mid+1,R,val,X);
		st[p]=merge(st[l(p)],st[r(p)]);
	}

	public:
		SegmentTree(int sz) : n(sz), st(4*n) {}
		SegmentTree(const vector<ll> &initialA): SegmentTree((int)initialA.size()){
			A=initialA;
			build(1,0,n-1);
		}
		void update(ll X,ll val){
			update(1,0,n-1,val,X);
		}
		ll getMaxi(){
			return st[1];
		}
		
	
};
SegmentTree st(A);
vector<int> adj[NAX];
vector<int> colors(NAX);
int tin[NAX];
int tout[NAX];
int bigch[NAX];
int timer=0;
vector<int> eulertour;
int dpsz[NAX];
void dfs(int node,int par=-1){
	tin[node]=timer;
	timer++;	
	eulertour.push_back(node);
	int maxi=0;
	dpsz[node]=1;
	int index=-1;
	for(auto el:adj[node]){
		if(el==par) continue;
		dfs(el,node);
		dpsz[node]+=dpsz[el];
		if(maxi<dpsz[el]){
			index=el;
			maxi=dpsz[el];
		}
	}

	bigch[node]=index;
	tout[node]=timer-1;
}
vector<int> colorstonumber(NAX);
void add(int color,int node=-1,bool t=false){
	int last=colorstonumber[color];
	sum[last+1]+=color;
	st.update(last+1,1);
	colorstonumber[color]=last+1;

}
void remove(int color,int node){
	int last=colorstonumber[color];
	sum[last]-=color;
	st.update(last,-1);
	colorstonumber[color]=last-1;

}
vector<ll> ans(NAX);
void solverec(int node,bool keep,int par){

	for(auto el:adj[node]){
		if(el==par || el==bigch[node]) continue;
		solverec(el,false,node);
	}

	if(bigch[node]!=-1){
		solverec(bigch[node],true,node);
	}
	for(auto el:adj[node]){
		if(el==par || el==bigch[node]) continue;
		for(int i=tin[el];i<=tout[el];i++){
			add(colors[eulertour[i]]);
		}
	}
	add(colors[node],node,true);
		int maxi=st.getMaxi();
		ll res=sum[maxi];
		ans[node]=res;
	if(!keep){
		for(int i=tin[node];i<=tout[node];i++){
			remove(colors[eulertour[i]],node);
		}		
	}

}
void solve(){

	cin >> n;
	for(int i=0;i<n;i++){
		cin >> colors[i];
	}

	for(int i=0;i<n-1;i++){
		int from,to;
		cin >> from >> to;
		from--;to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}



	dfs(0);
	solverec(0,1,-1);

	for(int i=0;i<n;i++){
		cout <<ans[i]<< " ";
	}
	cout <<"\n";


	



	
}
	
	

 
int main() {
	fastInp;
	//init();
	int tc=1;

	while(tc--){
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

