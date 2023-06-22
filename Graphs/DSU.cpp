#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
// we might use dsu when we have multiple connected components metnatrin w en cours mta3 
// el building mte3hom w theb some details alehom (size wala fiwset baadhoom wala 
// w etc.
// O(log *(n)) by operation
struct DSU {
	vector<int> e;
	vector<int> sz;
	DSU(int N) { e = vector<int>(N);
		sz=vector<int>(N);
		for(int i=0;i<N;i++){
			e[i]=i;
			sz[i]=1;
		} 
	}

	// get representive component (uses path compression)
	int get(int x) { return x==e[x] ? x : e[x] = get(e[x]); }

	bool same_set(int a, int b) { return get(a) == get(b); }

	int size(int x) { return sz[get(x)]; }

	bool unite(int x, int y) {  // union by size
		x = get(x), y = get(y);
		if (x == y) return false;
		if (sz[x] > sz[y]) swap(x, y);
		e[x] =y;
		sz[y]+=sz[x];
		return true;
	}
};

int main() {
	fastInp;
	int node_num, query_num;
	cin >> node_num >> query_num;
	DSU dsu(node_num);

	for (int i = 0; i < query_num; i++) {
		int type, u, v;
		cin >> type >> u >> v;
		if (type == 0) {
			dsu.unite(u, v);
		} else {
			cout << dsu.same_set(u, v) << endl;
		}
	}
}
