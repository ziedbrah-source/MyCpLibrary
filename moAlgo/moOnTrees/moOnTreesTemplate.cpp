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

const ll MOD = 998244353;
ll INF=2e18;
vector<int> eulertour;
// problem: https://www.spoj.com/problems/COT2/ (mo on trees :))
//u v : ask for how many different integers that represent the weight of nodes there are on the path from u to v.
const int NAX=2e5;
int heavyCH[NAX], chhead[NAX], sz[NAX];
int ch[NAX];
int par[NAX];
int dpth[NAX];
vector<vector<int>> adj(NAX);
int timer=0;
int en[NAX];
int out[NAX];
int ans[NAX];
int id[NAX];
int L[NAX];
int R[NAX];
int qlca[NAX]; // khater hachtna beha bech nzidoha fel query !!
int l,r;
int distinct=0;
vector<bool> vis(NAX);
bool isancestor(int u, int v){
    return en[u]<=en[v] && out[u]>=out[v];
}
void dfs(int u=0, int p=-1, int d=0){
	en[u]=timer++;
	eulertour.push_back(u);
    sz[u]=1;
    par[u]=p;
    dpth[u]=d;
    int mx = -1;
    int mxv=-1;
    heavyCH[u]=-1;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u,d+1);
        sz[u]+=sz[v];
        if(sz[v]>mx){
            mx=sz[v];
            mxv=v;
        }
    }
	eulertour.push_back(u);
	out[u]=timer;
	timer++;
    heavyCH[u]=mxv;
}

void buildHLD(int u=0,int c=0){
    if(u==-1)
        return ;
    chhead[u]=c;
    buildHLD(heavyCH[u], c);
    for(auto v: adj[u]){
        if(v==par[u] || v==heavyCH[u])
            continue;
        buildHLD(v,v);
    }
}



int HLD_LCA(int u, int v){
    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[u]]<dpth[chhead[v]])
            swap(u,v);
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v])
        swap(u,v);
    return u;
}


vector<int> numbers(NAX);


vector<int> inside(NAX);
void change(int node){
	distinct-=(inside[numbers[node]]>0);
	if(vis[node]){
		inside[numbers[node]]--;
		vis[node]=false;
	}else{
		vis[node]=true;
		inside[numbers[node]]++;
	}
	distinct+=(inside[numbers[node]]>0);

}
void update(int L,int R){
	while(r<R){
		r++;
		change(eulertour[r]);;

	}
	while(l>L){
		l--;
		change(eulertour[l]);
	}

	while(r>R){
		change(eulertour[r]);

		r--;
	}
	while(l<L){
		change(eulertour[l]);
		l++;
	}
}

void mo(){
	int B=sqrt((int)eulertour.size());
	sort(id,id+q,[B](int a,int b){
		return make_pair(L[a]/B,R[a])<make_pair(L[b]/B,R[b]);
	});
	l=0;
	r=-1;

	for(int i=0;i<q;i++){
		int querynb=id[i];
		if(qlca[querynb]!=-1){
			change(qlca[querynb]);
		}
		update(L[querynb],R[querynb]);
		ans[querynb]=distinct;
		if(qlca[querynb]!=-1){
			change(qlca[querynb]);
		}
	}
}
void solve(){	
	cin >> n >> q;
	numbers.resize(n);
	map<int,int> mp;
	set<int> s;
	for(int i=0;i<n;i++){
		cin >> numbers[i];
		s.insert(numbers[i]);
	}
	int code=0;
	for(auto el:s ){
		mp[el]=code;
		code++;
	}
	for(int i=0;i<n;i++){
		numbers[i]=mp[numbers[i]];
	}

	for(int i=0;i<n-1;i++){
		int from,to;
		cin >> from >> to;
		from -- ; to--;
		adj[from].push_back(to);
		adj[to].push_back(from);
	}

	dfs();
	buildHLD();
	for(int i=0;i<q;i++){
		int u,v;

		cin >> u >> v;
		u--;v--;
		id[i]=i;
		qlca[i]=HLD_LCA(u,v);
		if(qlca[i]==u || qlca[i]==v){
			qlca[i]=-1;
		}
		if(isancestor(u,v)){
			L[i]=en[u];
			R[i]=en[v];

		}else if(isancestor(v,u)){
			L[i]=en[v];
			R[i]=en[u];
		}else{
			if(en[u]>en[v]){
				swap(u,v);
			}
			L[i]=out[u];
			R[i]=en[v];
		}

	}
	mo();

	for(int i=0;i<q;i++){
		cout << ans[i] << "\n";
	}



}




int main() {
	fastInp;
	//init();
	//debug() << imie(s);
	//freopen("grids.in","r",stdin);
	//freopen("res.out","w",stdout);
	// __gcd <long long> (x, y);
	int tc=1;
	//debug() << imie(sieve);
	//cin >> tc;
	//cout << setprecision(10)<<fixed;

	while(tc--){
		//i++;
		//cout <<"Test " << i << ":" << "\n";

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
