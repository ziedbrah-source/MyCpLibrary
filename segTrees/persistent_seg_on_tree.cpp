#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

typedef long long ll;
typedef long double ld;
ll n,d,m;
// https://codeforces.com/group/Rilx5irOux/contest/537870/problem/K
// it's about how many values are above k from the path from node a to node b :)
const int LOG=19; 
const int MAX_VALUE=3e5+5; // the size of the ranges
int up[MAX_VALUE][LOG];
int tl = 0, tr = MAX_VALUE + 1;
vector<ll> vec(MAX_VALUE);
vector<int> depth(MAX_VALUE);

vector<ll> adj[MAX_VALUE];
vector<ll> valtoind(MAX_VALUE); // to map kol root l kol index!

// -----------------LCA-----------------------
int getLCA(int node1,int node2){
	// we want node1 lower than node2 // just bech netfedew IFS;
	if(depth[node2]>depth[node1]){
		swap(node1,node2);
	}
	int k=depth[node1]-depth[node2];
	for(int i=0;i<LOG;i++){
		if(k&(1<<i)){
			node1=up[node1][i];
		}
	}
	// if they are in the same line.
	if(node1==node2){
		return node1;
	}
	// now they are in the same depth.
	for(int i=LOG-1;i>=0;i--){
		if(up[node1][i]!=up[node2][i]){
			node1=up[node1][i];
			node2=up[node2][i];
		}
	}
	
	return up[node1][0];
	
}
//----------- persistent segment tree ---------------------
struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }

};

Vertex* build(int tl, int tr) { // not dynamic seg tree so just do the build once if there is multiple tests!
    if (tl == tr)
        return new Vertex(0);
    int tm = (tl + tr) / 2;
    return new Vertex(build(tl, tm), build(tm+1, tr));
}
int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

int query(Vertex* v,int tl,int tr,int l,int r){
	if(r<tl || l>tr){
		return 0;
	}
	if(tl>=l && tr<=r){
		return v->sum;
	}
	int tm=(tl+tr)/2;
	return query(v->l,tl,tm,l,r)+query(v->r,tm+1,tr,l,r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos) {
    if (tl == tr)
        return new Vertex(v->sum+1);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos));
}
vector<Vertex*> roots;
void dfs(int node,int par=0){
	roots.push_back(update(roots[valtoind[par]],tl,tr,vec[node]));
	valtoind[node]=roots.size()-1;
	for(auto el:adj[node]){
		if(el==par) continue;
		depth[el]=depth[node]+1;
		
		up[el][0]=node;
		
		for(int j=1;j<LOG;j++){
			up[el][j]=up[up[el][j-1]][j-1];
		}
		
		dfs(el,node);
	}
}

ll queryy(ll node,ll node1,ll k){
	ll rez1=query(roots[valtoind[node]],tl,tr,k,MAX_VALUE);
	ll rez2=query(roots[valtoind[node1]],tl,tr,k,MAX_VALUE);
	ll lcaa=getLCA(node,node1);
	ll rez3=query(roots[valtoind[lcaa]],tl,tr,k,MAX_VALUE);
	return rez1+rez2-2*rez3+(vec[lcaa]>=k);
}
Vertex* rr=build(tl, tr); // build outside if you have multiple tests w abda beha fel root awel mara pointi aleha!
void solve(){
	// it's 1 indexing
	roots.clear();
	
	cin >>n;
	cin >>m;
	for(int i=0;i<=n;i++) valtoind[i]=0;

	for(int i=1;i<=n;i++){
		cin >>vec[i];
	}


	for(int i=0;i<n-1;i++){
		ll from,to;
		cin >> from >>to;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}
	


	roots.push_back(rr);
	dfs(1);
	for(int i=0;i<m;i++){
		ll from,to,k;
		cin >> from >>to >>k;
		cout << queryy(from,to,k+1)<<'\n';
	}
	for(int i=0;i<=n;i++){
		adj[i].clear();
		depth[i]=0;
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

