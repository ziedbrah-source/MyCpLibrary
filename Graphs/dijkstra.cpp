#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
int n,m;
const int nax=2e5+10;
int parent[nax];
const long long INF=2e18;
vector<pair<int,long long>> adj[nax];
long long dist[nax];

void dijkstra(){
	for(int i=1;i<=n;i++){
		dist[i]=INF;
	}
	dist[1]=0;
	set<pair<long long,int>> q; // weight,index;
	q.insert({0,1});
	while(!q.empty()){
		
		int index=q.begin()->second;
		q.erase(*(q.begin()));
		
		for(int i=0;i<(int)adj[index].size();i++){
			if(dist[index]+adj[index][i].second<dist[adj[index][i].first]){
				q.erase({dist[adj[index][i].first],adj[index][i].first});
				dist[adj[index][i].first]=dist[index]+adj[index][i].second;
				parent[adj[index][i].first]=index;
				q.insert({dist[adj[index][i].first],adj[index][i].first});
			}
		}
	}
}

void printPath(){
	vector<int> path;
	
	for(int i=n;i!=1;i=parent[i]){
		path.push_back(i); 
	}
	path.push_back(1);
	reverse(path.begin(),path.end());
	for(int i=0;i<path.size();i++){
		cout << path[i] << " ";
	}
	cout <<"\n";
}
void solve(){
	cin >> n >> m;
	
	for(int i=0;i<m;i++){
		int from,to;
		long long w;
		cin >> from >> to >> w;
		adj[from].push_back({to,w});
		adj[to].push_back({from,w});
	}
	
	
	dijkstra();
	if(dist[n]==INF){
		cout <<-1<<"\n";
	}else{
		parent[1]=0;
		//cout << dist[n] << " ";
		printPath();
	}

	
	
	
}


int main() {
	fastInp;
	//freopen("socdist.in", "r", stdin);
	//freopen("socdist.out", "w", stdout);
	int tc;
	//cin >> tc;
	//cout << setprecision(10)<<fixed;
	//int i=1;

	//while(tc--){
		//cout <<"HELLO"<<endl;
		//cout << "Case #"<<i<<": " ;
		solve();
		//i++;
	//}

	
	/*while(true){
		cin >> n >> progK;
		if(n==0 && progK==0){
			break;
		}
		solve();
	}*/
	
}
