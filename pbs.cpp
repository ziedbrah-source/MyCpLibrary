#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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
#define         aff(v) for(auto e:v) cout<<e<<" ";cout<<endl;
#define mem1(a)           memset(a,-1,sizeof(a))
#define mem0(a)           memset(a,0,sizeof(a))
#define all(x)            (x).begin(),(x).end()
#define yes(check) cout << (check ? "Yes" : "No") << endl
typedef long long ll;
typedef long double ld;
ll n,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;

// problem: https://atcoder.jp/contests/agc002/tasks/agc002_d 
// parallel binary search, you use this techniqe with queries (sometimes even without queries);
// especially when you know that for every query you can binary search on the ans :)

const int NAX=1e5+5;
vector<ll> vec(NAX);

class DSU {

  private:

	vector<int> p, sz;

	// stores previous unites

	vector<pair<int &, int>> history;


  public:

	DSU(int n) : p(n), sz(n, 1) { iota(p.begin(), p.end(), 0); }


	int get(int x) { return x == p[x] ? x : get(p[x]); }


	void unite(int a, int b) {

		a = get(a);

		b = get(b);

		if (a == b) {
			history.push_back({sz[a], sz[a]});

			history.push_back({p[b], p[b]});
			return;
		 }

		if (sz[a] < sz[b]) { swap(a, b); }


		// save this unite operation

		history.push_back({sz[a], sz[a]});

		history.push_back({p[b], p[b]});


		p[b] = a;

		sz[a] += sz[b];

	}
	int getsz(int x){
		int a=get(x);
		return sz[a];
	}


	int snapshot() { return history.size(); }


	void rollback() {
		ll until=max(0,(int)history.size()-2);
		while (snapshot() > until) {

			history.back().first = history.back().second;

			history.pop_back();

		}

	}

};
int lll[NAX];
int rrr[NAX];
vector<pair<ll,ll>> edges;
DSU dsu(NAX);
int ans[NAX];
void upd(int x, int c) {
   
    if (c == 1) {
        dsu.unite(edges[x].first, edges[x].second);
    } else {
        dsu.rollback();
    }
}
ll how[NAX];
void rec(int l, int r, vector<int> queries, int &it) {
    if (queries.size() == 0) return;
    int md = l + (r - l) / 2;
     debug() << imie(l) imie(r) imie(queries) imie(md) imie(it);
    vector<int> left_queries, right_queries;
    while (it < md) {
        debug() << imie("aHAA") imie(it);
        upd(++it, 1);
    }
    while (it > md) {
        
        upd(it--, -1);
    }
    for (auto q : queries) {
        int a = dsu.get(lll[q]);


        int b = dsu.get(rrr[q]);
		ll szz=dsu.getsz(a);
		debug() << imie(szz);
		if(a!=b){
			szz+=dsu.getsz(b);
		}
		debug() << imie(queries) imie(lll[q]) imie(rrr[q]) imie(q) imie(a) imie(b) imie(szz) imie(how[q]);
    //    debug() << imie(q) imie(a) imie(b) imie(lll[q]) imie(rrr[q]) imie(it) imie(l) imie(r);
        if (szz>=how[q]) {
            ans[q] = md;
            left_queries.push_back(q);
        } else {
            right_queries.push_back(q);
        }
    }
    queries.clear();
    if (l == r) {
        return;
    }
    rec(l, md, left_queries, it);
    rec(md + 1, r, right_queries, it);
}

void solve(){
    cin >>n;
	vector<int> queries;
    edges.clear();
   
 //   debug() << imie(stMin.RSQ(0,n-1));
    ll m;
    cin >>m;
    int q;
  

    for(int i=0;i<m;i++){
        ll from,to;
        cin >> from >>to;
        from--;to--;
        edges.push_back({from,to});

    }

	cin >>q;

    for(int i=0;i<q;i++){
        cin >>lll[i] >> rrr[i];
        lll[i]--;
        rrr[i]--;
		cin >> how[i];
        queries.push_back(i);

    }
    int it=-1;
    rec(0,m-1,queries,it);
    for(int i=0;i<q;i++){
        cout << ans[i]+1<<' ';
        
    }
    cout <<'\n';



}
	
	

 
int main() {
	fastInp;
//	init();
	//debug() << imie(s);
	//freopen("grids.in","r",stdin);
	//freopen("res.out","w",stdout);
	// __gcd <long long> (x, y);
	int tc=1;
	//debug() << imie(sieve);
	//cin >> tc;
    debug() << imie(tc);
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
