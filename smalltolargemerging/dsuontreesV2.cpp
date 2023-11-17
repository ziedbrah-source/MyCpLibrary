// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 3e5 + 5;

int n, a[N], q;
int u, v;
vector<int> adj[N];
vector<int> queries[N];
int k[N], ans[N];
map<int, int> freq;
int sze[N], bchd[N];
int tin[N], tout[N], timer;
vector<int> ve;

void dfs(int u, int p = -1) {
    tin[u] = ++timer;
    ve.pb(u);
    int mxv = -1;
    int mx = 0;
    bchd[u] = -1;
    sze[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sze[u] += sze[v];
        if (sze[v] > mx) {
            mx = sze[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = timer;
}

void solve(int u, bool keep = 0, int p = -1) {
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        solve(v, 0, u);
    }
    if (bchd[u] != -1) {
        solve(bchd[u], 1, u);
    }
    freq[a[u]]++;
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            int x = ve[i];
            freq[a[x]]++;
        }
    }
    for (auto i : queries[u]) {
        ans[i] = freq[k[i]];
    }
    if (!keep) {
        freq.clear();
    }
}

void test_case() {
    ve.clear();
    timer = -1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        --u;
        --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> u >> k[i];
        u--;
        queries[u].pb(i);
    }
    dfs(0);
    solve(0);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << " ";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}

