#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
 
typedef long long ll;
typedef long double ld;
ll n,m,k,q,t,g,l,r;
const int prime=1e9+7;
// verification here : https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A
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
			st[p]=st[l(p)]+st[r(p)];
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
		st[p]=st[l(p)]+st[r(p)];
	}
	ll RSQ(int p,int L,int R,int LX,int RX){
		if(LX<=L&&R<=RX) return st[p];
		if(R<LX || L>RX) return 0;
		ll currVal=RSQ(l(p),L,(L+R)/2,LX,RX)+RSQ(r(p),(L+R)/2 +1 ,R,LX,RX);
		return currVal;
	}
	public:
		SegmentTree(int sz) : n(sz), st(4*n) {}
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
	cin >> n >> m;
	int tempn=n;

	vector<ll> vec(n);
	for(int i=0;i<tempn;i++) cin >> vec[i];
	SegmentTree st(vec);
	while(m--){
		int type;
	    cin >> type;
	    if(type==1){
			int index,val;
			cin >> index >> val;
			st.update(index,val);
		}else{
			int left,right;
			cin >> left >> right;
			right--;
			cout << st.RSQ(left,right) <<"\n";
		}
	}
}



	
 
 
 
int main() {
	fastInp;
	int tc=1;
	while(tc--){
		solve();
		//i++;
	}

	return 0;
}
