#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

typedef long long ll;
typedef long double ld;
ll n,q,d;
ll INF=2e18;
// tightUp for left, tightDown for right
// just to make sure we are always inside the range :)
// problem link : https://codeforces.com/contest/1808/problem/C
string answer;
int diff;
bool dp[19][10][10][2][2];
void solveRec(int digit,string& beg,string& lim,int mx,int mn,int tightUp,int tightDown,string res){
	debug() << imie(res);
	if(digit==0){
		debug() << imie(res);
		if(diff>(mx-mn)){
			debug() << imie(mx) imie(mn);
			diff=mx-mn;
			
			answer=res;
		}
		return;
	}
	if(dp[digit][mx][mn][tightUp][tightDown]) return;
	if(tightUp && tightDown){
		ll upperBound=lim[lim.size()-digit]-'0';
		ll lowerBound=beg[beg.size()-digit]-'0';
		debug() << imie(beg);
		debug() << imie(upperBound) imie(lowerBound);
		for(int i=lowerBound;i<=upperBound;i++){
			solveRec(digit-1,beg,lim,max(mx,i),min(mn,i),lowerBound==i,upperBound==i,res+to_string((i)));
		}
	}
	if(tightUp && !tightDown){
		ll upperBound=9;
		ll lowerBound=beg[lim.size()-digit]-'0';
		for(int i=lowerBound;i<=upperBound;i++){
		
			solveRec(digit-1,beg,lim,max(mx,i),min(mn,i),lowerBound==i,tightDown,res+to_string((i)));
		}
	}
	else if(!tightUp && tightDown){
		ll upperBound=lim[lim.size()-digit]-'0';
		ll lowerBound=0;
		for(int i=lowerBound;i<=upperBound;i++){
			solveRec(digit-1,beg,lim,max(mx,i),min(mn,i),tightUp,upperBound==i,res+to_string((i)));
		}
	}
	else if(!tightUp && !tightDown){
		ll upperBound=9;
		ll lowerBound=0;
		for(int i=lowerBound;i<=upperBound;i++){
			solveRec(digit-1,beg,lim,max(mx,i),min(mn,i),false,false,res+to_string((i)));
		}
	}
	dp[digit][mx][mn][tightUp][tightDown]=true;
}
void solve(){
	diff=10;
	string a,b;

	cin >> a >> b;
	if((int)a.size()!=(int)b.size()){
		for(int i=0;i<(int)a.size();i++){
			cout <<'9';
		}
		cout <<"\n";
		return;
	}
	 answer=a;
	 memset(dp,false,sizeof dp);
	solveRec((int)b.size(),a,b,0,9,true,true,"");
	cout << answer << "\n";
	
}
	
	

 
int main() {
	fastInp;
	int tc=1;
	while(tc--){
		solve();
		
	}

	return 0;
}

