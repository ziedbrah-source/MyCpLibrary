class HashedString {
  private:
	// change M and B if you want
	static const ll M = (1LL << 61) - 1;
	static const ll B;

	// pow[i] contains B^i % M
	static vector<ll> pow;

	// p_hash[i] is the hash of the first i characters of the given string
	vector<ll> p_hash;

	__int128 mul(ll a, ll b) { return (__int128)a * b; }
	ll mod_mul(ll a, ll b) { return mul(a, b) % M; }

  public:
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() < s.size()) {
			pow.push_back(mod_mul(pow.back(), B));
		}
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = (mul(p_hash[i], B) + s[i]) % M;
		}
	}

	ll getHash(int start, int end) {
		ll raw_val =
			p_hash[end + 1] - mod_mul(p_hash[start], pow[end - start + 1]);
		return (raw_val + M) % M;
	}
};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<ll> HashedString::pow = {1};
const ll HashedString::B = uniform_int_distribution<ll>(0, M - 1)(rng);
HashedString hs(h);
hs.getHash(i + 1 - n.size(), i);
