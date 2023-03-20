// THEY DON'T KNOW ME SON
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
const int nax=1e5+5;
//LCA VERIFICATION : https://www.spoj.com/problems/LCA/
struct LCA{
	vector<int> depth;vector<int> euler;int timer=0;
	vector<int> last;
	vector<int> tree;
	int maxi=1e8;
	int n;
	int sz;
	LCA(vector<vector<int>>&adj,int root=0){
		n=(int)adj.size();
		depth.resize(n);
		last.resize(n);
		dfs(adj,0,-1);
		sz=(int)euler.size();
		while(__builtin_popcount(sz)!=1){
		sz++;
			euler.push_back(maxi);
		}
		tree.resize(2*sz);
		for(int i=0;i<sz;i++){
			tree[sz+i]=euler[i];
		}
		buildSeg();
	
	}
	void dfs(vector<vector<int>> &adj,int node,int par){
		if(par!=-1){
			depth[node]=1+depth[par];
		}
		euler.push_back(node);
		timer++;
		for(auto to:adj[node]){
			if(to!=par){
				dfs(adj,to,node);
				timer++;
				euler.push_back(node);
			}
		}
		last[node]=timer-1;
	}
	int merge(int nd1,int nd2){
		if(nd1==nd1==maxi){
			return maxi;
		}
		int maxii=max(nd1,nd2);
		if(maxii==maxi){
			int mini=min(nd1,nd2);
			return mini;
		}	
		if(depth[nd1]<depth[nd2]){
			return nd1;
		}else{
			return nd2;
		}

	}
	void buildSeg(){
		for(int i=sz-1;i>=1;i--){
			tree[i]=merge(tree[2*i],tree[2*i+1]);
		}
	}
	int query(int node1,int node2){
		return query(1,0,sz-1,min(last[node1],last[node2]),max(last[node1],last[node2]));

	}
	int query(int node,int node_low, int node_high,int query_low, int query_high){
		if(node_high < query_low || node_low>query_high) return maxi;
		if(node_low>=query_low &&node_high<=query_high){
			return tree[node];
		}

		int mid=(node_low+node_high)/2;
		return merge(query(2*node,node_low,mid,query_low,query_high),query(2*node+1,mid+1,node_high,query_low,query_high));

}

};
void solve(){
	cin >> n;
	vector<vector<int>> adj(n);
	for(int i=0;i<n;i++){
		int m;
		cin >> m;
		for(int j=0;j<m;j++){
			int nd;
			cin >> nd;
			nd--;
			adj[i].push_back(nd);
			adj[nd].push_back(i);
		}
	}

	LCA lca=LCA(adj);
	cin >> q;
	while(q--){
		int u,v;
		cin >> u >> v;
		u--;v--;

		int res=lca.query(u,v);
		cout << res+1<<"\n";
	}

	

	
}
	
	

int main() {
	int tc=1;
	cin >> tc;
	int i=0;
	while(tc--){
		i++;
		cout <<"Case " << i << ":" << "\n";
		
		solve();
		
	}

	return 0;
}
