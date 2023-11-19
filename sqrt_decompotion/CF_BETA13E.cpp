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
#define yes(check) cout << (check ? "YES" : "NO") << endl
typedef long long ll;
typedef long double ld;
ll n,q,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
// problem: https://codeforces.com/contest/13/problem/E
// SQRT decomp and some dp!!!!
const int NAX=2e5+5;
int nxt[NAX];
int lst[NAX];
int times[NAX];
int sqrtt=320;
int getblock(int v){
  if(v>=n) return n;
  return v/sqrtt;
}
vector<ll> vec;
void update(int index){
  if(getblock(index)!=getblock(index+vec[index])){
      lst[index]=index;
      nxt[index]=min(n,index+vec[index]);
      times[index]=1;

  }else{
    lst[index]=lst[index+vec[index]];
    nxt[index]=nxt[index+vec[index]];
    times[index]=1+times[index+vec[index]];
  }
}
void solve(){
  cin >>n;
  vec.resize(n);
  cin >>q;
  for(int i=0;i<n;i++){
    cin >>vec[i];
  }
  for(int i=n-1;i>=0;i--) update(i);
  debug() << imie("hné");
  for(int i=0;i<q;i++){
    int t;
    cin >>t;
    if(t){
      int hole;
      cin >>hole;
      hole--;
      ll cntr=0;
      ll last;
      for(int j=hole;j<n;j=nxt[j]){
        debug() << imie(j) imie(nxt[j]) imie(times[j]);
        cntr+=times[j];
        last=lst[j];
      }
      cout << last+1 <<" "<< cntr<<'\n';
      
    }else{
      int hole;int p;
      cin>>hole>>p;
      hole--;
      vec[hole]=p;
      for(int i=hole;i%sqrtt;i--){
        update(i);
      }
      update((hole/sqrtt)*sqrtt);

    }

  }
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


