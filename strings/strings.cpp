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



/**


// H(s)=(B+s1​)(B+s2​)…(B+sk​)modM // independent ordering!!!!!!

Since this hash requires the modular inverse, there's an extra $\log M$ factor
in the time complexity.
* //
* 
* //
* */


class HashedStringUnordered {
  public:
	// change M and B if you want
	static const ll M = (1LL << 61) - 1;
	static const ll B;
	static __int128 mul(ll a, ll b) { return (__int128)a * b; }
	static ll mod_mul(ll a, ll b) { return mul(a, b) % M; }

  private:
	// pow[i] contains P^i % M
	static vector<ll> pow;

	// p_hash[i] is the hash of the first i characters of the given string
	vector<ll> p_hash;

  public:

  	static ll inv(ll base, ll MOD) {
	ll ans = 1, expo = MOD - 2;
	while (expo) {
		if (expo & 1) {
			ans = mod_mul(ans, base);
		}
		expo >>= 1;
		base = mod_mul(base, base);
	}
	return ans;
	}
	// basdlo string ken b string wala vector<ll> ken b vector!
	HashedStringUnordered(const vector<ll> &s) : p_hash(s.size() + 1) {
		
		p_hash[0] = 1;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = mod_mul(p_hash[i], (B+(s[i]))) % M;
            debug() << imie(i) imie(s[i]) imie(B) imie(p_hash[i+1]);
		}
	}

	ll getHash(int start, int end) {
		ll raw_val =
			mod_mul(p_hash[end + 1],inv(p_hash[start],M));
		return (raw_val + M) % M;
	}
};
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const ll HashedStringUnordered::B = uniform_int_distribution<ll>(0, M - 1)(rng);
// EndCodeSnip

const auto M = HashedStringUnordered::M;
const auto B = HashedStringUnordered::B;
const auto mul = HashedStringUnordered::mul;
const auto mod_mul = HashedStringUnordered::mod_mul;
const auto inv=HashedStringUnordered::inv;

