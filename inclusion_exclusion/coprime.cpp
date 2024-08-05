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
#define yes(check) cout << (check ? "Yes" : "No") << endl
typedef long long ll;
typedef long double ld;

ll n,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const ll MOD = 998244353;
ll INF=2e18;
//problem: https://codeforces.com/contest/1780/submission/274538409
// basically it's an inclusion exclusion problem
// each A[i] nchoufou 9adeh andou men wehed coprime bih -> (i-9adeh men wehed not coprime)
// and this is a standard inclusion exclusion problem!
// and the second part is that we need to add how much those numers contribute to the result
// of a[i] -> same!!! inclusion exclusion -> why?
// because it's really the same xD |A U B| =>  eli houma yet9esmou ala kal B +eli yet9esmou ala B 9adeh yaatiw? w ken fama nes zedou fel zouz -> enna7iwohom!
// el idea howa ennou tnejem tekhou maaloumet meli mahomch coprime 9adeh ycontributiwlek!!!!!!

const int NAX=3e5+5;
ll howmuch[NAX];
ll adeh[NAX];
ll mp[NAX];
ll reducer[NAX];

vector<ll> vec;
void init(){
    for(ll i = 1 ; i<NAX ; i++){
        reducer[i] = i ;
    }
    for(ll i = 2 ; i<NAX ; i++){
        if(reducer[i]==i){
            for(ll j = i+i ; j<NAX ; j+=i){
                reducer[j] = i ;
            }
        }
    }
}
vector<ll> prep(ll n)
{
    vector<ll> ret ;
    while(n>1){
        ret.push_back(reducer[n]) ;
        ll x = reducer[n] ;
        while(n%x==0) n/= x ;
    }
    return ret ;
}
pair<ll,ll> go(int index){
    vector<ll> primes=prep(vec[index]);

   
   // primes.push_back(vv);
        ll mask=primes.size();
    ll sum=0;

    ll sum1=0;
    for(int i=1;i<(1<<mask);i++){
        ll pop=__builtin_popcount(i);
        ll val=1;
            for(int j=0;j<mask;j++){
                if((1<<j)&i){
                    val*=primes[j];
                }
            }
        if(pop%2){  

            sum+=howmuch[val];
            sum1+=adeh[val];
        }else{
            sum-=howmuch[val];
            sum1-=adeh[val];

        }
    }
    return {sum,sum1};
}


void del(int index){
       vector<ll> primes=prep(vec[index]);
    
   
    ll mask=primes.size();

    for(int i=1;i<(1<<mask);i++){
        ll pop=__builtin_popcount(i);
        ll val=1;
             for(int j=0;j<mask;j++){
                 if((1<<j)&i){
                     val*=primes[j];
                 }
             }
       howmuch[val]--;
       adeh[val]-=index;
      
    
    }
}

void add(int index){
    vector<ll> primes=prep(vec[index]);
    
    ll mask=primes.size();
    for(int i=1;i<(1<<mask);i++){
        ll pop=__builtin_popcount(i);
        ll val=1;
             for(int j=0;j<mask;j++){
                 if((1<<j)&i){
                     val*=primes[j];
                 }
             }
       howmuch[val]++;
       adeh[val]+=index;
    }
}
void solve(){
    cin >>n;
    vec.resize(n);
    for(int i=0;i<n;i++){
        cin >> vec[i];
    }
    sort(all(vec));
    ll sum=0;
    ll rezz=0;
    debug() << imie(vec);

    for(int i=0;i<n;i++){

        // remove 9abli;
        if(i>=1){
            del(i-1);
            sum-=(i-1);
        }

        ll rez=(i>0?(i-1)-go(i).first:0); // rez howa 9adeh men wehed coprime
        debug() << imie(i) imie(rez) imie(go(i).second) imie(rez*i);
        ll summ=rez*i-(sum-go(i).second)-rez;
        rezz+=summ;
       
        if(i>=1){
            add(i-1);
            sum+=(i-1);
        }
        add(i);
        sum+=i;
    

    }
    cout << rezz <<'\n';

}
  
  

 
int main() {
  fastInp;
  init();
  int tc=1;

    debug() << imie(tc);
  

  while(tc--){
    
    solve();
    
  }

  return 0;
}

