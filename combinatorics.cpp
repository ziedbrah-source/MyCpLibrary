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
