
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);


typedef long long ll;
typedef long double ld;
ll n,q,d;

const ll MOD = 998244353;
ll INF=2e18;

// problem Link : https://cses.fi/problemset/result/5774825/
ll dp[20][2][2][10];
ll solverec(string& num,int digNum,bool tight,bool leading,int lastDig){
	if(digNum==0){
		return 1;
	}
	if(dp[digNum][tight][leading][lastDig]!=-1) return dp[digNum][tight][leading][lastDig];
	int upperBound=tight? num[(int)num.length()-digNum]-'0':9;
	ll answer=0;
	for(int i=0;i<=upperBound;i++){
		if(i==lastDig && !leading) continue;
		if(i==0 && leading){
			answer+=solverec(num,digNum-1,tight&&(upperBound==i),leading,i);
		}else{
			answer+=solverec(num,digNum-1,tight&&(upperBound==i),false,i);
		}
	}
	return dp[digNum][tight][leading][lastDig]=answer;
}
void solve(){
	string s1;
	string s2;
	ll a, b;
	cin >> a >> b;
	a--;
	s1=to_string(a);
	s2=to_string(b);
	debug() << imie(s2);
	memset(dp,-1, sizeof dp);
	ll val=solverec(s2,(int)s2.size(),1,1,0);
	ll val2=0;
	debug() << imie(val);
	memset(dp,-1, sizeof dp);
	 if(a!=-1) val2= solverec(s1,(int)s1.size(),1,1,0);
	cout << val - val2 <<"\n";
	
}
	
	

 
int main() {
	fastInp;
	int tc=1;
	while(tc--){

		solve();
		
	}

	return 0;
}


