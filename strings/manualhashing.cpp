// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
// problem : http://www.usaco.org/index.php?page=viewproblem2&cpid=529 
class HashedString {
  public:
	// change M and B if you want
	static const ll M = (1LL << 61) - 1;
	static const ll B;

	ll add(ll a,ll b){
		return (a+b)%M;
	}
	ll minus(ll a,ll b){
		return ((a-b)%M+M)%M;
	}
	// p_hash[i] is the hash of the first i characters of the given string
	vector<ll> p_hash;

	__int128 mul(ll a, ll b) { return (__int128)a * b; }
	ll mod_mul(ll a, ll b) { return mul(a, b) % M; }
	// pow[i] contains B^i % M
	static vector<ll> pow;

	ll getpow(int index){
		return pow[index];
	}
  
	ll retB(){
		return B;
	}
	ll retM(){
		return M;
	}
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() < s.size()) {
			pow.push_back(mod_mul(pow.back(), B));
		}
	}

};
// 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<ll> HashedString::pow = {1};
const ll HashedString::B = uniform_int_distribution<ll>(0, M - 1)(rng);
void solve(){
	string s,t;
	cin >> s >> t;
	HashedString hs(s);
	ll B=hs.retB();
	ll M=hs.retM();
	ll hashT=0;
	for(int i=0;i<(int)t.size();i++){
		hashT= hs.add(hashT,hs.mod_mul(t[i]-'a'+1,hs.getpow(i)));
	}
	vector<ll> currPref;
	string res="";
	for(int i=0;i<(int)s.size();i++){
		//debug() << imie(currPref);
		res+=s[i];
		if((int)currPref.size()==0){
			currPref.push_back(hs.mod_mul(s[i]-'a'+1,hs.getpow((int)currPref.size())));
		}else{
			currPref.push_back(hs.add(currPref.back(),hs.mod_mul(s[i]-'a'+1,hs.getpow((int)currPref.size()))));
		}
		
		if((int)res.size()>=(int)t.size()){
			int len=(int)t.size();
			ll ha=currPref.back();
			ll hash2=0;
			if((int)currPref.size()==len){

			}else{
				hash2=currPref[(int)currPref.size()-len-1];
				
			}
			ha=hs.minus(ha,hash2);
			ll ha1=hashT;
			if((int)currPref.size()==len){
			}else{
				ha1=hs.mod_mul(hashT,hs.getpow((int)currPref.size()-len));
			}
			if(ha==ha1){
				currPref.resize((int)currPref.size()-len);
				if(res.size()==t.size()){
					res="";
				}else{
					res.resize((int)currPref.size());
				}
				
			}

		}
		
	}	
	cout << res << "\n";
	
}
	
	

 
int main() {
	//fastInp;
	//init();
	//debug() << imie(s);
	//freopen("censor.in","r",stdin);
	//freopen("censor.out","w",stdout);
	// __gcd <long long> (x, y);
	int tc=1;
	//debug() << imie(sieve);
	//cin >> tc;
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

