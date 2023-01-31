//============================================================================
// Name        : Brahmi Zied
// Author      : brahZied
// Version     : 2022
// Description : Road to expert
//============================================================================
/*
    STAY ORGANIZED
    CHANGE YOUR APPROACH
    BE CONFIDENT
*/
// when you train write the algos from 0
//Think different approaches 
//(trace TestCase,think with symbols,think with PICS,
//numberTheory,bs,dp,greedy,graphs,shortest paths,mst,
//dsu,LCA(binary lifting?),hashing(strings))
//Stay Calm
// IN TRAINING DO NOT SEE WRONG TEST CASES AFTER SUBMITTING!
//Look for special cases
//Beware of overflow and array bounds
//Think the problem backwards
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

typedef long long ll;
typedef long double ld;
ll n,m,g,d,c;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

/** 
 * problem link : https://codeforces.com/gym/101808/problem/B
 * HASHING (with double hashes and size of hash :) 
 * 
 * notes on hash : 
 * when you have a sequence and you want to hash it like here ; 
 * you can do like here, when the first time it enters you give it the value mp.size()
 * and that value is the distinct value for a sequence . from,to for example :)
 * 
 * you can also do it as a representation in a base link : we have maxVal , u and v 
 * we can make it u*(maxVal+1)+v; (we surely need to make sure that if u> v we swap it , or the reverse)
 * but this approach might be too costly , so if the values are big, avoid it .
 * 
 * and now we go to the hash part.
 * 
 * if we care about the order : let s= 1 2 3 4 , 1*Base puiss (n) + 2 * base puiss(n-1)...(don't forget about the MOD :) )
 * if we don't care about the order: the hash will be base puissance(1)+puissnace(2)... so we don't care about where the occurence happens :)
 * 
 * //ans+=tk[j-i][{firstH,secondH}]; we make two hashes, 
 * because we know that if one thing is the same , it will give the same hash1 and hash2 , 
 * but if hash1 is the same and 
 * hash2 is not! -> it's surely not the same 
 * also you need to make sure that the values are less than the base , otherwise shit can happen :)
 * 
 *SMART IDEA :) GLHF
 * 
 **/ 
ll base1=304933,base2=4395853,p1=1e9+7,p2=1e9+9,pow1[6005],pow2[6005];
map<pair<int,int>,int> tk[3000];
map<pair<int,int>,int> mp;
void solve(){
	cin >> n;
	vector<int> vec(n);
	mp.clear();
	for(int i=0;i<n;i++){
		// unique representation theorem, linear algebra
		tk[i].clear();
		int from,to;
		cin >> from >> to;
		if(from>to){
			swap(from,to);
		}
		if(!mp.count({from,to})) mp[{from,to}]=mp.size();
		vec[i]=mp[{from,to}];
	}
	ll ans=0;
	for(int i=0;i<n;i++){
			ll firstH=0;
			ll secondH=0;
			for(int j=i;j<n;j++){
				firstH=firstH+pow1[vec[j]];
				firstH=firstH%p1;
				secondH=secondH+pow2[vec[j]];
				secondH=secondH%p2;
				// double HASH, cause if it's really the same one, it will have the same hash!
				
				ans+=tk[j-i][{firstH,secondH}];
				tk[j-i][{firstH,secondH}]++;
				
			}
		}
		
		cout << ans << "\n";
		
	}
	
 
int main() {
	fastInp;
	pow1[0]=1;
	pow2[0]=1;
	for(int i=1;i<6005;i++){
		pow1[i]=pow1[i-1]*base1%p1;
		pow2[i]=pow2[i-1]*base2%p2;
	}
	//freopen("mootube.in","r",stdin);
	//freopen("t.out","w",stdout);
	int tc=1;
	//debug() << imie(sieve);
	cin >> tc;

	//cout << setprecision(10)<<fixed;
	while(tc--){

		solve();
		
	}

	return 0;
}
