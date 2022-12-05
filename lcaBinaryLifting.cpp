 
typedef long long ll;
ll n,m,q,t,h,g;
const int mxN=1e4+5;
vector<int> adj[mxN];
const int LOG=15; 
vector<int> depth(mxN);
int up[mxN][LOG];
// verification done here : https://www.spoj.com/problems/LCASQ/ :)
void dfs(int node){
	
	for(int i=0;i<(int)adj[node].size();i++){
		
		depth[adj[node][i]]=depth[node]+1;
		
		up[adj[node][i]][0]=node;
		
		for(int j=1;j<LOG;j++){
			up[adj[node][i]][j]=up[up[adj[node][i]][j-1]][j-1];
		}
		
		dfs(adj[node][i]);
	}
}

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
void solve(){
	cin >> n;	
	for(int i=0,number;i<n;i++){
		cin >> number; // this is the number of nodes that are children of the i'th
		// node :)
		while(number--){
			int node;
			cin >> node;
			adj[i].push_back(node);
			
		}
	}
	dfs(0);
	cin >> q;
	while(q--){
		int n1,n2;
		cin >> n1 >> n2;
		cout << getLCA(n1,n2)<<"\n";
	}
	
}


	
 
 
 
int main() {
	fastInp;
	solve();
	return 0;
}
