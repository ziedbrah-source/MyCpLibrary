const int nax=1e6+12;
vector<int> vec(nax+1);
vector<int> primes;

// less than nax log(nax);
void init_sieve(){
	
	for(int i=2;i<=nax;i++){
		if(vec[i]==0){
			primes.push_back(i);
			for(int j=i;j<=nax;j+=i){
				vec[j]=i;
			}
		}
	}
}

// number of divisors of N;
// O(log N);

long long numDiv(long long N) {
	long long PF_idx = 0, PF = primes[PF_idx];
	// start from ans = 1
	long long ans=1;
		while (PF * PF <= N) {
	long long power = 0;
	// count the power
	while (N % PF == 0) { N /= PF; power++; }
	ans*=(power+1);
	
	// according to the formula
	PF = primes[++PF_idx];
	}
	if (N != 1) ans*=2;
	// (last factor has pow = 1, we add 1 to it)
	return ans;

}	



// a power b  mod mod ; in log(b);
const int mod=1e9+7;

long long power(long long a,long long b){
	if(b==0){return 1;}
	long long res=power(a,b/2);
	res=(res*res)%mod;
	if(b&1) res=(res*a)%mod;
	return res;
}
