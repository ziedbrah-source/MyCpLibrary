const int MAXN = 1e6;

long long fac[MAXN + 1], inv[MAXN + 1];
	
/** the prob here is when we use division with mod, it does not work correctly!
 * or when we divide x by y, it's like we multiply x with the inverse of y 
 * and we know that multiplation with mod works without any modification
 * so we get the inverse of y (in the mod p) with a Fermat's Little Theorem
 * and we do it all like we are using the multiplication
	
		
/** Computes x^y modulo p in O(log p) time. */
long long exp(long long x, long long y, long long p) {
	long long res = 1; x %= p;
	while (y) {
		if (y & 1) {
			res *= x; res %= p; 
		}
		x *= x; x %= p;
		y >>= 1;
	}
	return res;
}

/** Precomputes n! from 0 to MAXN. */
void factorial(long long p) {
	fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) {
		fac[i] = fac[i - 1] * i % p;
	}
}

/** Precomputes all modular inverse factorials from 0 to MAXN in O(n + log p) time */
/** we use the fact that inv(n!)=inv(n!)*(inv(n+1)*n+1)=inv((n+1)!)*n+1 
 * (we use this because computing inverse factorias 
 * online can be costly (if we add log every time.. why not once right? :p)
 * */
void inverses(long long p) {
	inv[MAXN] = exp(fac[MAXN], p - 2, p);
	for (int i = MAXN; i >= 1; i--) {
		inv[i - 1] = inv[i] * i % p;
	}
}
		
/** Computes nCr mod p */
long long choose(long long n, long long r, long long p) {
	return fac[n] * inv[r] % p * inv[n - r] % p;
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
