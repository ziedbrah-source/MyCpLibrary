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
 * An alternative solution without frequency tables would be to hash the substrings
that we're trying to match. Since order doesn't matter, we need to modify our
hash function slightly.

In particular, instead of computing the polynomial hash of the substrings,
compute the product $(B + s_1)(B + s_2) \dots (B + s_k) \bmod M$ as the hash
(again, using two modulos). This hash is nice because the relative order of the
letters doesn't matter, as multiplication is commutative. Furthermore,
as any two strings with different frequency tables map to different polynomials
in $B$, they hash to the same value with probability at most $\frac{|N|}{M}$
over the choice of $B$.

Since this hash requires the modular inverse, there's an extra $\log M$ factor
in the time complexity.
* //
* 
* //
* */


#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// BeginCodeSnip{HashedString}
class HashedString {
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
// EndCodeSnip

const auto M = HashedString::M;
const auto B = HashedString::B;
const auto mul = HashedString::mul;
const auto mod_mul = HashedString::mod_mul;
ll inv(ll base, ll MOD) {
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

string n, h;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> h;
	if (n.size() > h.size()) return cout << 0, 0;
	HashedString hs(h);

	set<ll> good;
	ll h_hsh = 1, n_hsh = 1;
	for (int i = 0; i < n.size(); i++) {
		// Compute product hashes
		h_hsh = mod_mul(h_hsh, B + h[i] - 'a');
		n_hsh = mod_mul(n_hsh, B + n[i] - 'a');
	}

	// like this
	for (int i = n.size() - 1; i < h.size(); i++) {
		if (i >= n.size()) {
			// Update product hashes using modular inverse
			h_hsh = mod_mul(h_hsh, inv(B + h[i - n.size()] - 'a', M));
			h_hsh = mod_mul(h_hsh, B + h[i] - 'a');
		}
		if (n_hsh == h_hsh) {
			good.insert(hs.getHash(i + 1 - n.size(), i));
		}
	}

	cout << good.size() << '\n';
}
