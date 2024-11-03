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