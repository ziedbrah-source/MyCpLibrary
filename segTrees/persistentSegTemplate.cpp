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

const ll MOD = 998244353;
ll INF=2e18;
//problem: https://www.spoj.com/problems/KQUERY/
class PersistentSeg{
	public:
		int n;
		vector<ll> A;
		vector<vector<ll>> st;

		PersistentSeg(int sz): n(sz),A(sz),st(4*sz){

		};
		PersistentSeg(vector<ll>& initial):PersistentSeg((int)initial.size()){
			A=initial;
			build(1,0,n-1);
		}

		void build(int node,int L,int R ){
			if(L==R){
				st[node]={A[L]};
				return;
			}

			int mid=(L+R)/2;
			build(2*node,L,mid);
			build(2*node+1,mid+1,R);
			  merge(st[2*node].begin(), st[2*node].end(),
        			st[2*node+1].begin(), st[2*node+1].end(),
        			inserter(st[node], st[node].begin()));	
			

		}

		int query(int node,int L,int R,int Lx,int Rx,int val){ // gives for X how many  value less than X or equal in that range
			if(L>Rx || R<Lx) return 0;
			if(L>=Lx && R<=Rx){
				vector<ll> & v=st[node];
				return lower_bound(v.begin(),v.end(),val+1)-v.begin();
			}
			int mid=(L+R)/2;
			return query(2*node,L,mid,Lx,Rx,val)+query(2*node+1,mid+1,R,Lx,Rx,val);
		}
};
void solve(){

	cin >> n;
	vector<ll>A(n);
	for(int i=0;i<n;i++) cin >>A[i];
	PersistentSeg st(A);
	ll q;
	cin >> q;

	for(int i=0;i<q;i++){
		int left,right,val;
		cin >> left>>right >> val;
		left--;right--;
		int number=(right-left+1)-st.query(1,0,n-1,left,right,val);
		cout << number << "\n";
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

/*
   Some insights:
    .Binary search
    .Graph representation
    .Write brute force code
    .Change your approach
 
 
 */

