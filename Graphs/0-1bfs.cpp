#include <bits/stdc++.h>
using namespace std;
// probLink : https://www.codechef.com/problems/REVERSE
int main() {
	// your code goes here
	int n,m;
	const int nax=1e5+5;
	vector<pair<int,int>> adj[nax];
	const int INF=1e9+5;
	vector<int> height(nax,INF);
	bool visited[nax];
	cin >> n >> m;
	map<pair<int,int>,bool> mp;
	for(int i=0;i<m;i++){
	    int from,to;
	    cin >> from >> to;
	    from--;to--;
	    adj[from].push_back({to,0});
	    adj[to].push_back({from,1});
	}
	//0-1 bfs;
	deque<int> q;
	visited[0]=true;
	height[0]=0;
	q.push_back(0);
	while(!q.empty()){
	    int node=q.front();
	    q.pop_front();
	    for(int i=0;i<(int)adj[node].size();i++){
	            int no=adj[node][i].first;
	            int val=adj[node][i].second;
	            visited[adj[node][i].first]=true;
	            if(height[node]+val<height[adj[node][i].first]){
	                height[adj[node][i].first]=height[node]+val;
	                if(val){
	                   q.push_back(adj[node][i].first);
	                }else{
	                   q.push_front(adj[node][i].first);
	                }
	            }
	    }
	}
	
	if(!visited[n-1]){
	    cout << -1 << "\n";
	}else{
	    cout << height[n-1] << "\n";
	}
	   
	return 0;
}
