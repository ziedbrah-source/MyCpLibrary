// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
int m,s,k;
const int K=101;
vector<int> types[K];
const int NAX=1e5+5;
int dist[NAX][K];
vector<int> adj[NAX];
// problem: https://codeforces.com/contest/986/problem/A
// concept: multi source bfs.
// you need to start from multiple vertexs and you need to get the minimum distance for each other
// vertex to anyu vertex you started with.
bitset<NAX> visited;
void bfs(int type){
	for(int i=0;i<n;i++) visited[i]=false;
	queue<int> q;
	for(int i=0;i<(int)types[type].size();i++){
		q.push(types[type][i]);
		visited[types[type][i]]=true;
		dist[types[type][i]][type]=0;
	}

	while(!q.empty()){
		int nd=q.front();
		q.pop();
		for(auto el:adj[nd]){
			if(visited[el]) continue;
			dist[el][type]=dist[nd][type]+1;
			visited[el]=true;
			q.push(el);
		}
	}


}
void solve(){

	cin >> n >> m >> k >> s;

	for(int i=0;i<n;i++){
		int tp;
		cin >> tp;
		types[tp].push_back(i);
	}
	for(int i=0;i<m;i++){
		int from,to;
		cin >> from >> to;
		from--;to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	for(int i=1;i<=k;i++){
		bfs(i);
	}

	for(int i=0;i<n;i++){
		vector<int> v;
		for(int j=1;j<=k;j++){
			v.push_back(dist[i][j]);
		}
		sort(v.begin(),v.end());
		ll sum=0;
		for(int j=0;j<s;j++){
			sum+=v[j];
		}
		cout << sum << " ";
	}
	cout <<"\n";


	
}
	
	

 
int main() {
	fastInp;
	int tc=1;

	while(tc--){
		
		solve();
		
	}

	return 0;
}



