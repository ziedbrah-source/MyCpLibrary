#include <bits/stdc++.h>
//#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,d;


ll INF=2e18;

// __builtin_popcount() Function
const int NAX=35005;
ll dp[102][NAX];
ll cost=0;
vector<ll> vec;
vector<ll> seen;
ll k;
ll nex[NAX];
ll lastseen[NAX];
ll pre[NAX];
ll curr_l=1;
ll curr_r;
// problem: // works with min or max :)
// https://codeforces.com/contest/1527/problem/E
// dp[i][k]=min(dp[j][k-1]+cost(j+1,i)) // normal complexity is O(n² * k); // this is the formula , works even for max. but for max you need to reverse the satisfability
// cost(j+1,i) satisfies this: for every i<=j ,C(i,j+1) -C(i,j)>= C(i+1,j+1)-C(i+1,j) => if this is satisfied you can use the optimization (divide and conquer and even others)
// we reverse the state, it's now dp[k][i] => for each layer k, we compute all i from 1 to n in n log(n)
// -> complexity is (nk *log(n));
void fix(int l, int r)
{
    
	//while(curr_l < l) rem(curr_l++);
    while(curr_l < l) {
        if(nex[curr_l]<=curr_r){
            cost-=(nex[curr_l]-curr_l);
        }

        curr_l++;
    }
	//while(curr_l > l) add(--curr_l);
    while(curr_l>l){
        
        --curr_l;
        if(nex[curr_l]<=curr_r){
            cost+=(nex[curr_l]-curr_l);
        }
       // debug() << imie()
    }
	//while(curr_r < r) add(++curr_r);
    while(curr_r < r) {
        curr_r++;
        if(pre[curr_r]>=curr_l ){
            cost+=(curr_r-pre[curr_r]);
        }

    }
	//while(curr_r > r) rem(curr_r--);
    while(curr_r > r){
        if(pre[curr_r]>=curr_l) {
            cost-=(curr_r-pre[curr_r]);
        }


        curr_r--;
    }
    debug() << imie(cost) imie(l) imie(r) imie(curr_l) imie(curr_r) imie("2");
}

void solve(int l,int r,int optl,int optr,ll level){ // this is the imprtant part;
    if(l>r) return;
    int mid=(l+r)/2;
    pair<ll,ll> best={INF,-1};
    for(int k=optl;k<=min(mid,optr);k++){
        fix(k,mid); // this is to calculate the cost function when you are going!
         best = min(best, {(k ? dp[level-1][k-1] : 0) + cost, k});
         debug() << imie(k) imie(mid) imie(cost);

    }
    dp[level][mid]=best.first;
    int opt=best.second;
    solve(l,mid-1,optl,opt,level);
    solve(mid+1,r,opt,optr,level);
}

 
void solve(){

   
    cin >>n;
    curr_r=n;
    cin >>k;
    vec.resize(n+1);
    

    for(int i=1;i<=n;i++){
        cin >>vec[i];
        if(lastseen[vec[i]]!=0){
            nex[lastseen[vec[i]]]=i;
            cost+=(i-lastseen[vec[i]]);
        }
       
        lastseen[vec[i]]=i;
        
        nex[i]=i;
        dp[1][i]=cost;
        
    }
    for(int i=1;i<=n;i++){
        lastseen[i]=0;
    }

    for(int i=n;i>0;i--){
       
        if(lastseen[vec[i]]!=0){
            pre[lastseen[vec[i]]]=i;
        }
       
        lastseen[vec[i]]=i;
        
        pre[i]=i;
    }
    debug() << imie(cost);
    for(int i=1;i<=n;i++){
        debug() << imie(pre[i]) imie(nex[i]) imie(i);
    }
    for(int i=2;i<=k;i++){
        solve(1,n,1,n,i);
    }

    cout << dp[k][n]<<'\n';
    
}
	
	

 
int main() {
	fastInp;
	int tc=1;
	while(tc--){
		solve();
	}

	return 0;
}
