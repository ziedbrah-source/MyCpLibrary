#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,d;

const int NAX=2e5+5;
// binary lifting verification : https://cses.fi/problemset/task/1687
const int LOG=19;
int up[NAX][LOG];
void solve(){
	cin >> n >> q;
	memset(up,-1,sizeof up);
	up[0][0]=-1;
	for(int i=2;i<=n;i++){
		int boss;
		cin >> boss;
		boss--;
		up[i-1][0]=boss;
	}

	for(int i=0;i<n;i++){
		for(int j=1;j<LOG;j++){
			if(up[i][j-1]!=-1) up[i][j]=up[up[i][j-1]][j-1];
		}
	}

	for(int i=0;i<q;i++){
		int em,k;
		cin >> em >> k;
		em--;

		for(int j=0;j<LOG;j++){
			if(k&(1<<j)){
				em=up[em][j];
				if(em==-1) break;
			}
		}

		if(em==-1){
			cout << em << "\n";
		}else{
			cout << em+1<<"\n";
		}
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


