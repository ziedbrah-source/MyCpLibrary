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
// problem https://codeforces.com/gym/316406/problem/A

const ll MOD = 998244353;
ll INF=2e18;
const int NAX=2e5+5;
int left[NAX];
int right[NAX];	
class SegmentTree{
	private: 
		int n;
		vector<ll> A,st;
	
	int l(int p) {return p<<1;}
	int r(int p) {return (p<<1)+1;}
	
	void build(int p,int L,int R){
		if(L==R){
			st[p]=A[L];
		}else{
			int mid=(R+L)/2;
			build(l(p),L,mid);
			build(r(p),mid+1,R);
			st[p]=min(st[l(p)],st[r(p)]);
		}
	}
	void update(int p,int L,int R,int val, int X){
		if(X==R&&L==X){
			st[p]=val;
			return;
		}
		if(R<X || L>X) return;
		int mid=(R+L)/2;
		update(l(p),L,mid,val,X);
		update(r(p),mid+1,R,val,X);
		st[p]=min(st[l(p)],st[r(p)]);
	}
	ll RSQ(int p,int L,int R,int LX,int RX){
		if(LX<=L&&R<=RX) return st[p];
		if(R<LX || L>RX) return INF;
		ll currVal=min(RSQ(l(p),L,(L+R)/2,LX,RX),RSQ(r(p),(L+R)/2 +1 ,R,LX,RX));
		return currVal;
	}
	public:
		SegmentTree(int sz) : n(sz), st(4*n,INF) {}
		SegmentTree(const vector<ll> &initialA): SegmentTree((int)initialA.size()){
			A=initialA;
			build(1,0,n-1);
		}
		void update(int X,int val){
			update(1,0,n-1,val,X);
		}
		ll RSQ(int LX,int RX){
			return RSQ(1,0,n-1,LX,RX);
		}
		
	
};
void solve(){
	cin >> n;
	vector<ll> pref(n);
	for(int i=0;i<n;i++){
		cin >> pref[i];
		if(i){
			pref[i]=pref[i]+pref[i-1];
		}
	}


	vector<int> left(n+10);
	vector<int> right(n+10);
	for(int i=1;i<n;i++){
		cin >> left[i] >> right[i];
		left[i]--;
		right[i]--;
	}
	vector<ll> dp(n,INF);
	dp[0]=0;
	SegmentTree st(dp);
	for(int i=1;i<n;i++){
		int from,to;
		from=left[i];
		to=right[i];
		/*for(int j=from;j<=to;j++){
			if(j==0){
				dp[i]=min(dp[i],dp[j]+pref[i]);
			}else{
				dp[i]=min(dp[i],dp[j]+pref[i]-pref[j-1]);
			}
		}*/
		dp[i]=pref[i]+st.RSQ(from,to);
		st.update(i,dp[i]-pref[i-1]);
		

	}
	for(int i=0;i<n;i++){
		cout << dp[i] << " ";
	}
	cout <<"\n";

	
}
	
	

 
int main() {
	fastInp;

	int tc=1;
	

	while(tc--){
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

