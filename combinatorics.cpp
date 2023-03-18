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

/** miller rabin primality test: 
 * // C++ program Miller-Rabin primality test
#include <bits/stdc++.h>
using namespace std;

// Utility function to do modular exponentiation.
// It returns (x^y) % p
int power(int x, unsigned int y, int p)
{
	int res = 1;	 // Initialize result
	x = x % p; // Update x if it is more than or
				// equal to p
	while (y > 0)
	{
		// If y is odd, multiply x with result
		if (y & 1)
			res = (res*x) % p;

		// y must be even now
		y = y>>1; // y = y/2
		x = (x*x) % p;
	}
	return res;
}

// This function is called for all k trials. It returns
// false if n is composite and returns true if n is
// probably prime.
// d is an odd number such that d*2 = n-1
// for some r >= 1
bool miillerTest(int d, int n)
{
	// Pick a random number in [2..n-2]
	// Corner cases make sure that n > 4
	int a = 2 + rand() % (n - 4);

	// Compute a^d % n
	int x = power(a, d, n);

	if (x == 1 || x == n-1)
	return true;

	// Keep squaring x while one of the following doesn't
	// happen
	// (i) d does not reach n-1
	// (ii) (x^2) % n is not 1
	// (iii) (x^2) % n is not n-1
	while (d != n-1)
	{
		x = (x * x) % n;
		d *= 2;

		if (x == 1)	 return false;
		if (x == n-1) return true;
	}

	// Return composite
	return false;
}

// It returns false if n is composite and returns true if n
// is probably prime. k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k)
{
	// Corner cases
	if (n <= 1 || n == 4) return false;
	if (n <= 3) return true;

	// Find r such that n = 2^d * r + 1 for some r >= 1
	int d = n - 1;
	while (d % 2 == 0)
		d /= 2;

	// Iterate given number of 'k' times
	for (int i = 0; i < k; i++)
		if (!miillerTest(d, n))
			return false;

	return true;
}

// Driver program
int main()
{
	int k = 4; // Number of iterations

	cout << "All primes smaller than 100: \n";
	for (int n = 1; n < 100; n++)
	if (isPrime(n, k))
		cout << n << " ";

	return 0;
}
**/
