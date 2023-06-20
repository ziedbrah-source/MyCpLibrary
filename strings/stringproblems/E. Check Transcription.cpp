// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define         aff(v) for(auto e:v) cout<<e<<" ";cout<<endl;
#define mem1(a)           memset(a,-1,sizeof(a))
#define mem0(a)           memset(a,0,sizeof(a))
#define all(x)            (x).begin(),(x).end()
#define sz(x)             (int)((x).size())
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;
// problem: https://codeforces.com/contest/1056/problem/E (hashing)
const ll MOD = 998244353;
ll INF=2e18;
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
void solve(){
	string s,s1;
	cin >> s >> s1;
	HashedString hs(s1);
	int cnt0=0;
	int cnt1=0;
	for(int i=0;i<(int)s.size();i++){
		if(s[i]=='0') cnt0++;
		if(s[i]=='1') cnt1++;
	}
	ll sum=0;
	int zerofirstpos=-1;
	int	onefirstpos=-1;
	for(int i=(int)s.size()-1;i>=0;i--){
		if(s[i]=='1'){
			onefirstpos=i;
		}else{
			zerofirstpos=i;
		}

	}
	debug() << imie(cnt0) imie(cnt1);
	n=(int)s1.length();
	for(ll i=1;i<n;i++){
		//i is the size of 0;
		ll cnt=cnt0*i;
		//debug() << imie(cnt);
		if(cnt>=n) continue;
		ll needed=n-cnt;
		if(needed%cnt1!=0) continue;
		int index=0;
		ll hash0=-1;
		ll hash1=-1;
		int sz1=needed/cnt1;
		debug() << imie(i) imie(sz1);
		int j=0;
		bool t=true;
		while(j<n){

			debug() << imie(j) imie(i) imie(index);
			int val=(s[index]-'0');
			debug() << imie(val);
			if(val==1){
				if(hash1==-1){
					hash1=hs.getHash(j,j+sz1-1);
				}else{
					if(hash1!=hs.getHash(j,j+sz1-1)){
						
						t=false;
						break;
					}
				}
				j+=sz1;
			}else{
				if(hash0==-1){
				
					hash0=hs.getHash(j,j+i-1);
					debug() << imie("out") imie(j+i-1) imie(j) imie(hash0);
				}else{
					if(hash0!=hs.getHash(j,j+i-1)){
						debug()<< imie(s1[j+i-1]) imie(s1[j]);
						debug() << imie("inn") imie(j+i-1) imie(j) imie(hs.getHash(j,j+i-1));
						t=false;
						break;
					}
				}
				j+=i;
			}
			index++;
		}
		debug() << imie(i) imie("hné") imie(t) imie(hash1);
		if(hash1==hash0 || t==false) continue;
		debug() << imie(i) imie("hnéééé 2");
		sum++;


	}

	cout << sum << "\n";




}
	
	

 
int main() {
	fastInp;
	//init();
	//debug() << imie(s);
	//freopen("grids.in","r",stdin);
	//freopen("res.out","w",stdout);
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

