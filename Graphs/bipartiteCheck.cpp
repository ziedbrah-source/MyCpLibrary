#include <bits/stdc++.h>
using namespace std;

int main()
{
	//----------
	int INF=1e8;
	bool isBipartite=true;
	vector<int> color(n,INF);
	queue<int> q; q.push(i);
	color[i]=0;
	while(!q.empty() && isBipartite){
		int u = q.front();q.pop();
		for(int j=0;j<(int)vec[u].size();j++){
			int v=vec[u][j];
			if(color[v]==INF){
			color[v]=1-color[u];
			q.push(v);
		}else if(color[v]==color[u]){
			isBipartite=false; break;
			}
		}		
	}
	
	//---------------
	// working and tested code.
    return 0;
}
