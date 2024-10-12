#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,d;


// problem: https://atcoder.jp/contests/abc375/tasks/abc375_g 
// basically check if the edge i is critcal or no (critical means that deleting it will make the distance from 1 to n bigger)
// the solution is this: 
// basically we need to check if numer of ways to get to node1 from 1 (with the minimum distance of course) *
// (number of ways to go from node2 to n (with minimum distance ofcourse)==numbers of ways to get to n? if yes -> this edge is critical)

const ll MOD = (1LL << 61) - 1;
const ll MOD1=1e9+7;
__int128 mul(ll a, ll b) { return (__int128)a * b; }

ll mod_mul(ll a, ll b) { return mul(a, b)%MOD; }

ll mod_mul1(ll a, ll b) { return mul(a, b); }
ll INF=2e18;

// __builtin_popcount() Function

const int nax=2e5+5;
vector<pair<int,long long>> adj[nax];
long long dist[nax];
long long dist1[nax];
long long dist2[nax];
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
				
				q.insert({dist[adj[index][i].first],adj[index][i].first});
			}
		}
	}
    for(int i=1;i<=n;i++){
        dist1[i]=dist[i];
		dist[i]=INF;
	}
	dist[n]=0;
	
	q.insert({0,n});
	while(!q.empty()){
		
		int index=q.begin()->second;
		q.erase(*(q.begin()));
		
		for(int i=0;i<(int)adj[index].size();i++){
			if(dist[index]+adj[index][i].second<dist[adj[index][i].first]){
				q.erase({dist[adj[index][i].first],adj[index][i].first});
				dist[adj[index][i].first]=dist[index]+adj[index][i].second;
			
				q.insert({dist[adj[index][i].first],adj[index][i].first});
			}
		}
	}

    for(int i=1;i<=n;i++){
        dist2[i]=dist[i];
		dist[i]=INF;
	}
}


ll dp[nax]; // number of ways to go from 1 to i; 
ll dp2[nax]; // numer of ways to go from i to n;
// I using the mod because the numbers are really big -> it's kinda hashing. so put a good mod.
ll howmuch(int who,int par=-1){
    if(who==1) return dp[who]=1;
    if(dp[who]!=-1) return dp[who];
    ll rez=0;
    for(auto el:adj[who]){
        if(el.first==par) continue;
        if(dist1[el.first]+el.second==dist1[who]){
            rez+=howmuch(el.first,who);
            rez%=MOD;
        }
    }
    return dp[who]=rez;

}

ll howmuch1(int who,int par=-1){
    if(who==n) return dp2[who]=1;
    
    if(dp2[who]!=-1) return dp2[who];
    ll rez=0;
    for(auto el:adj[who]){
        if(el.first==par) continue;
         if(dist1[who]+el.second+dist2[el.first]==dist1[n]){
            rez+=howmuch1(el.first,who);
            rez%=MOD;
        }
    }
    return dp2[who]=rez;
}



vector<pair<ll,pair<ll,ll>>> edges;
void solve(){

    cin >>n;
    ll m;
    cin >>m;
    memset(dp,-1,sizeof dp);
    memset(dp2,-1,sizeof dp2);
    for(int i=0;i<m;i++){
        ll from,to,w;
        cin >>from >>to>>w;
        adj[from].push_back({to,w});
        adj[to].push_back({from,w});
        edges.push_back({from,{to,w}});
    }
    dijkstra();
    howmuch(n);
    howmuch1(1);
    for(int i=1;i<=n;i++){
        // it gets ac even without doing this, but it feels more logic to me.
        if(dp[i]==-1) dp[i]=0;
        if(dp2[i]==-1) dp2[i]=0;
    }
    for(int i=0;i<m;i++){
        // basically we need to check if numer of ways to get to node1 from 1 (with the minimum distance of course) * (number of ways to go from node2 to n (with minimum distance ofcourse)==numbers of ways to get to n? if yes -> this edge is critical)
        pair<ll,pair<ll,ll>> p=edges[i];
        ll howmany=dp[n];
        if(dist1[p.first]+p.second.second+dist2[p.second.first]==dist1[n]){
            
            ll how1=mod_mul(dp[p.first],dp2[p.second.first]);
            
            if(how1==howmany){
                cout<<"Yes"<<'\n';
            }else{
                cout <<"No"<<'\n';
                
            }
        }else if(dist1[p.second.first]+p.second.second+dist2[p.first]==dist1[n]){
            ll how2=mod_mul(dp[p.second.first],dp2[p.first]);
             if(how2==howmany){
                cout<<"Yes"<<'\n';
            }else{
                cout <<"No"<<'\n';
                
            }
        }else{
            cout <<"No"<<'\n';
        }
        
        continue;
    }
}
int main() {
	fastInp;
	int tc=1;
	while(tc--){
		
		solve();
		
	}

	return 0;
}

