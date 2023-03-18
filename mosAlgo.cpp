
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

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

const int nax=3e4+5;
const int Qax=2e5+5;
const int Max=2e6+5;
int tab[nax];
int id[Qax]; // id of the query after sorting it .
int X[Qax]; // left of the query i
int Y[Qax]; // right of the query i;
int freq[Max];
int ans[Qax];
ll counter;
int l,r;

// mo's algorithm : verification : https://www.spoj.com/problems/DQUERY/
void add(int val){
	freq[val]++;
	if(freq[val]==1) counter++;
}

void remove(int val){
	freq[val]--;
	if(freq[val]==0) counter--;
	
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
		ans[id[i]]=counter;
	}
	
	
}
 
void solve(){
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> tab[i];
	}
	
	cin >> q;
	for(int i=0;i<q;i++){
		id[i]=i;
		cin >> X[i] >> Y[i];
		X[i]--;Y[i]--;
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
