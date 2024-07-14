#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,d;
const int SIGMA = 26;
const int MAX_N = 6e5;
// problem: https://atcoder.jp/contests/abc362/tasks/abc362_g
// basically it's about searching multiple substrings in a text -> you prepare the automata after that you search :p
// the problem talsk about giveing how many substring in that string equal to the queried string :)
int trie[MAX_N][SIGMA];
int nodes = 1;
vector<int> leaf[MAX_N]; // terminaisons!
vector<int> g[MAX_N]; // the graph of suffixes! (graph of fails melkhr)
string s; // the text
int seen[MAX_N];
int ans[MAX_N];
int fail[MAX_N];  // fail[u] = the failure link for node (melkhr el maximal other suffix :p)
void add_word(const string &word, const int &idx) {

	int node = 1;

	for (char ch : word) {

		if (trie[node][ch - 'a'] == 0) { trie[node][ch - 'a'] = ++nodes; }

		node = trie[node][ch - 'a'];

	}

	leaf[node].push_back(idx);

}
// building the suffix links! and the failure (the failure is for sigmas)
void build(){
	queue<int> q; // bfs style level by level
	int node= 1;
	fail[node]=1; // comme quoi el suffix mta3 el empty howa empty

	for(int i=0;i < SIGMA;i++){
		if(trie[node][i]){
			fail[trie[node][i]]=1;
			q.push(trie[node][i]);
		}else{
			trie[node][i]=1;
		}
	}

	while(!q.empty()){ // building the automata!
		int node=q.front();
		q.pop();
		for(int i=0;i<SIGMA;i++){
			if(trie[node][i]){
				fail[trie[node][i]]=trie[fail[node]][i];
				q.push(trie[node][i]);
			}else{
				trie[node][i]=trie[fail[node]][i]; // dp style comme quoi khater deja enti haseb bel lvl bel lvl!
			}
		}
	}

	for (int i = 2; i <= nodes; i++) { g[fail[i]].push_back(i); } // building the tree of the suffixs cool!


}

void search() {

	int node = 1;

	for (char ch : s) {

		node = trie[node][ch - 'a'];

		seen[node]++;

	}

}
int dfs(int node) {

	int sol = seen[node];

	for (int son : g[node]) { sol += dfs(son); }

	for (int idx : leaf[node]) { ans[idx] = sol; }

	return sol;

}
void solve(){
	cin >> s >> n;
	vector<string> words(n);
	for(int i=0;i<n;i++){
		cin >> words[i];
		add_word(words[i],i);
	}

	build();
	search();
	dfs(1);

	for(int i=0;i<n;i++){
		cout << ans[i]<<" ";
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



