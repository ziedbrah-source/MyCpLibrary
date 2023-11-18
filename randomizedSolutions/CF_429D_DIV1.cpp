
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
ll n,q,k,m,d;
const ll prime=1e9+7;
const ll prime2=998244353;
const ll prime3=7901;

const int MAX_N = 100'005;
const ll MOD = 1e9 + 7;
ll INF=2e18;
int maxi=0;
int mini=2e8;

const int nax=3e5+5;
const int Qax=3e5+5;
const int Max=nax;
int tab[nax];
int id[Qax]; // id of the query after sorting it .
int X[Qax]; // left of the query i
int Y[Qax]; // right of the query i;
int freq[Max];
int ans[Qax];
ll counter;
int l,r;
// problem: https://codeforces.com/contest/840/problem/D
// MO and randomized solution.
// let's see how we calcule the probability;
// so say K=5 -----> in another time the value will be there more than 4/5 of the time.
// so the probability of picking it randomly is: 100-(4/5)^80=99% so you win :D

// mo's algorithm : verification : https://www.spoj.com/problems/DQUERY/
void add(int val){
	freq[val]++;
}

void remove(int val){

	freq[val]--;
	
}
void update(int index){
	
	while(r<Y[index]){
		r++;
		add(tab[r]);
	}
	while(l>X[index]){
		l--;
		add(tab[l]);
	}
	while(r>Y[index]){
		remove(tab[r]);
		r--;
	}
	
	while(l<X[index]){
		remove(tab[l]);
		l++;
	}
	
}
int K[nax];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void mo(){
	
	int B=sqrt(nax);
	sort(id,id+q,[B](int a,int b){
		
		pair<int,int> p1={X[a]/B,Y[a]};
		pair<int,int> p2={X[b]/B,Y[b]};
		return p1<p2;
	});
	counter=0;
  
	l=0;
	r=-1;
	for(int i=0;i<q;i++){
		update(id[i]);
  //  debug() << imie(id[i]) imie(st) imie((Y[id[i]]-X[id[i]]+1)/(K[id[i]]));
  ll cntr=(Y[id[i]]-X[id[i]]+1)/K[id[i]];
  ans[id[i]]=-1;
  ll mini=2e18;
  for(int j=0;j<80;j++){
    ll v=uniform_int_distribution<int>(X[id[i]],Y[id[i]])(rng);
    if(freq[tab[v]]>cntr){
      mini=min(mini,(ll)tab[v]);
    }
  }
  if(mini!=2e18){
    
    ans[id[i]]=mini;
  }
   // auto it=st.upper_bound({(Y[id[i]]-X[id[i]]+1)/K[id[i]],2e18});
    /*if(it==st.end()){
      ans[id[i]]=-1;
    }else{
      debug() << imie(id[i]) imie(st) imie((Y[id[i]]-X[id[i]]+1)/(K[id[i]])) imie(*(it));
      	ans[id[i]]=(*it).second;
    }*/

	
	}
	
	
}
 
void solve(){
 // srand(1);
	cin >> n;
  	cin >> q;
	for(int i=0;i<n;i++){
		cin >> tab[i];
	}
	

	for(int i=0;i<q;i++){
		id[i]=i;
		cin >> X[i] >> Y[i];
		X[i]--;Y[i]--;
    cin >>K[i];
	}
	mo();
	
	for(int i=0;i<q;i++){
		cout << ans[i] << "\n";
	}
}


 
int main() {
	fastInp;
	int tc=1;

	while(tc--){

		solve();
		
	}

	return 0;
}