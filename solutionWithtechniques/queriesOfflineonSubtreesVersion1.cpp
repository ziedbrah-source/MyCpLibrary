//============================================================================
// Name        : Brahmi Zied
// Author      : brahZied
// Version     : 2022
// Description : Road to expert
//============================================================================
/*
    STAY ORGANIZED
    CHANGE YOUR APPROACH
    BE CONFIDENT
*/
// when you train write the algos from 0
//Think different approaches 
//(trace TestCase,think with symbols,think with PICS,
//numberTheory,bs,dp,greedy,graphs,shortest paths,mst,
//dsu,LCA(binary lifting?),hashing(strings))
//Stay Calm
// IN TRAINING DO NOT SEE WRONG TEST CASES AFTER SUBMITTING!
//Look for special cases
//Beware of overflow and array bounds
//Think the problem backwards
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

typedef long long ll;
typedef long double ld;
ll n,m,g,d,c;
const ll prime=1e9+7;
const ll prime2=998244353;

const int nax=2e5;
/**
 * Credit goes to : https://www.youtube.com/watch?v=QeJ6sPc5Ufo
 * O(nlog(n)) 
 * Problem solved here: 
 * Given a tree with n nodes rooted at node 1
 * each node i in the tree have a value a[i].
 * You are given q queries:
 * for each queries you are given 2 values u and k
 * you need to print the number of nodes in the subtree of u which have value k.
 * 
 * Offline queries (first time for me )
 *  INPUT TEST 
 *5
 *1 2 2 3 3
 *1 2
 *1 5
 *2 3
 *2 4
 *3
 *1 3
 *1 1
 *2 2
 **/
vector<int> adj[nax];
vector<int> queries[nax];
int ans[nax];
int k[nax];
int id[nax];
map<int,int> freq[nax];
vector<int> vals(nax,0);
void mrg(int par,int node){
	if(freq[id[par]]<freq[id[node]]){
		swap(id[par],id[node]);
	}

	for(auto p:freq[id[node]]){
		freq[id[par]][p.first]+=p.second;
	}
}
void dfs(int node,int p){
	freq[id[node]][vals[node]]=1;

	for(auto no:adj[node]){
		if(no==p) continue;
		dfs(no,node);
		mrg(node,no);
	}

	for(auto i:queries[node]){
		ans[i]=freq[id[node]][k[i]];
	}


}

void solve(){

	cin >> n;
	for(int i=0;i<n;i++){
		cin >> vals[i];
		id[i]=i;
	}
	for(int i=0;i<n-1;i++){
		int from,to;
		cin >> from >> to;
		from--;
		to--;
		adj[from].push_back(to);
		adj[to].push_back(from);	
	}
	ll q;
	cin >> q;
	for(int i=0;i<q;i++){
		int node, val;
		cin >> node >> val;
		node--;
		queries[node].push_back(i);
		k[i]=val;
	}

	dfs(0,-1);


	for(int i=0;i<q;i++){
		cout << ans[i] << " " ;
	}
	cout <<"\n";
}
 
int main() {
	fastInp;
	//freopen("mootube.in","r",stdin);
	//freopen("t.out","w",stdout);
	int tc=1;
	
	//cin >> tc;
	//cout << setprecision(10)<<fixed;
	//tempTC=tc;
	while(tc--){
		//cout <<"HELLO"<<endl;
		//cout << "Case #"<<i<<": " ;
		//cout << setprecision(10) << "\n";
		solve();
		
	}

	return 0;
}
