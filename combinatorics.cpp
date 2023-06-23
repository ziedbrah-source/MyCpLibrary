#include <iostream>
using namespace std;
using ll = long long;

const int MAXN = 1e6;
const int MOD = 1e9 + 7;

ll fac[MAXN + 1];
ll inv[MAXN + 1];

ll exp(ll x, ll y, ll p) {
	ll res = 1; x %= p;
	while (y) {
		if (y & 1) {
			res *= x; res %= p; 
		}
		x *= x;
		x %= p;
		y >>= 1;
	}
	return res;
}

void factorial() {
	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) {
		fac[i] = fac[i - 1] * i % MOD;
	}
}

void inverses() {
	inv[MAXN] = exp(fac[MAXN], MOD - 2, MOD);
	for (int i = MAXN; i >= 1; i--) {
		inv[i - 1] = inv[i] * i % MOD;
	}
}

ll choose(int n, int r) {
	return fac[n] * inv[r] % MOD * inv[n - r] % MOD;
}

// another inverse :
// complexity between log(m) and O(n(1/3))
// mech dima tkharej shiha aucune idée aleh. use it if you really need it .
int inv(int i) {
  return i <= 1 ? i : m - (long long)(m/i) * inv(m % i) % m;
}

int main() {
	factorial();
	inverses();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		cout << choose(a, b) << '\n';
	}
}


/** dearrangement is giving n points , how many permutations where there is no pi=i !  */

vector<ll> dp(MAXN+1,0);

void dearrang(){
	// dp[i]=(i-1)*(dp[i-2]+dp[i-1])
	dp[0]=1;
	dp[1]=0;

	for(int i=2;i<=MAXN;i++){
		dp[i]=(i-1)*dp[i-2]+(i-1)*dp[i-1];
	}
}

// binomial and DP:
/** Computes nCk mod p using dynamic programming */
int binomial(int n, int k, int p) {
	// dp[i][j] stores iCj
	vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

	// base cases described above
	for (int i = 0; i <= n; i++) {
		/*
		 * i choose 0 is always 1 since there is exactly one way
		 * to choose 0 elements from a set of i elements
		 * (don't choose anything)
		 */
		dp[i][0] = 1;
		/*
		 * i choose i is always 1 since there is exactly one way
		 * to choose i elements from a set of i elements
		 * (choose every element in the set)
		 */
		if (i <= k) { dp[i][i] = 1; }
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 1; j <= min(i, k); j++) {
			if (i != j) {  // skips over the base cases
				// uses the recurrence relation above
				dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % p;
			}
		}
	}

	return dp[n][k];  // returns nCk modulo p
}
