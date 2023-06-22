#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool visited[(int)1e5 + 5], on_stack[(int)1e5 + 5];
vector<int> adj[(int)1e5 + 5];
vector<int> cycle;
int N, M;
// cycle detection on directed graph.
// problem : https://cses.fi/problemset/task/1678/
bool dfs(int n) {
	visited[n] = on_stack[n] = true;
	for (int u : adj[n]) {
		if (on_stack[u]) {
			cycle.push_back(n);  // start cycle
			on_stack[n] = on_stack[u] = false;
			return true;
		} else if (!visited[u]) {
			if (dfs(u)) {  // continue cycle
				if (on_stack[n]) {
					cycle.push_back(n);
					on_stack[n] = false;
					return true;
				} else {  // found u again
					cycle.push_back(n);
					return false;
				}
			}
			if (!cycle.empty())  // finished with cycle
				return false;
		}
	}
	on_stack[n] = false;
	return false;
}
int main() {
	// take input, etc
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
	}
	for (int i = 1; cycle.empty() && i <= N; i++) dfs(i);
	if (cycle.empty()) cout << "IMPOSSIBLE";
	else {
		reverse(cycle.begin(), cycle.end());
		cout << cycle.size() + 1 << "\n";
		for (int n : cycle) cout << n << " ";
		cout << cycle.at(0);
	}
}