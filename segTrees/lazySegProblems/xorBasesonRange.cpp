#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
int n,d;
// problem: https://codeforces.com/group/Rilx5irOux/contest/538817/problem/H
// check if you can get maximum xor when using values values from range [l,r]
// and sometimes you update point update and sometimes range update with an "and".
const int NAX=1e5+5;
 
struct xorBasis {
    int basis[31];
    void clear(){
        memset(basis, 0,sizeof basis);
    }
    void addVector(int x) {
        for (int i = 30; i >= 0; i--) {
            if (((1 << i) & x)  == 0) continue;
            if (basis[i])
                x^= basis[i];
            else {
                basis[i] = x;
                return;
            }
        }
    }
    vector<int> givevalues(){
        vector<int> vv;
        for(int i=30;i>=0;i--){
            if(basis[i]){
                vv.push_back(basis[i]);
            }
        }
        return vv;
    }
    int size() {
        int sz = 0;
        for (int i = 0; i < 31; i++) {
            if (basis[i])
                sz++;
        }
        return sz;
    }
    int getmax(){
        int value=0;
        for(int i=30;i>=0;i--){
            if(value&(1<<i)) continue;
            if(basis[i]){
                value^=basis[i];
            }
        }
        return value;
    }
	bool can(int x){
		for(int i=30;i>=0;i--){
			if(x&(1<<i) && basis[i]){
				x^=basis[i];
			}
		}
		return x==0;
	}
};
 
const int neutral=(1<<30)-1;
xorBasis tree[4*NAX];
int lazy[4*NAX];
bool has_lazy[4*NAX];
xorBasis merge(xorBasis b1,xorBasis b2){
    vector<int> vv=b2.givevalues();
    for(auto el:vv){
        b1.addVector(el);
    }
    return b1;
}
 
void propagate(int id,int ns,int ne){
    if(!has_lazy[id]) return;
    if(ns!=ne){
        int idleft= id*2+1;
        int idright=id*2+2;
        lazy[idleft]&=lazy[id];
        lazy[idright]&=lazy[id];
        has_lazy[idleft]=true;
        has_lazy[idright]=true;
    }
    vector<int> xorvals=tree[id].givevalues();
    tree[id].clear();
    for(auto el:xorvals){
        tree[id].addVector(el&lazy[id]);
    }
    lazy[id]=neutral;
    has_lazy[id]=false;
}
 
void update1(int index,int value,int id=0, int ns=0,int ne=n-1 ) {
    propagate(id,ns,ne);
    if(index<ns || index>ne){
        return;
    }
    if(ns==index && ne==index){
        tree[id].clear();
        tree[id].addVector(value);
        return;
    }
    int md=(ns+ne)/2;
    update1(index,value,id*2+1,ns,md);
    update1(index,value,id*2+2,md+1,ne);
    tree[id]=merge(tree[2*id+1],tree[2*id+2]);
}
 
xorBasis get(int qs,int qe,int id=0,int ns=0,int ne=n-1){
    propagate(id,ns,ne);
    if(qe<ns || qs>ne){
        xorBasis newbase;
        newbase.clear();
        return newbase;
    }
    if(ns>=qs && ne<=qe){
        return tree[id];
    }
    int md=(ns+ne)/2;
    return merge(get(qs,qe,id*2+1,ns,md),get(qs,qe,id*2+2,md+1,ne));
}
 
void update2(int qs,int qe,int value,int id=0, int ns=0,int ne=n-1 ){
    // to propage later
    propagate(id,ns,ne);
    if(ns>qe || ne<qs){
        return;
    }
    if(ns>=qs && ne<=qe){
        lazy[id] =value;
        has_lazy[id]=true;
        propagate(id,ns,ne);
        return;
    }
    int md=(ns+ne)/2;
    update2(qs,qe,value,id*2+1,ns,md);
    update2(qs,qe,value,id*2+2,md+1,ne);
    tree[id]=merge(tree[2*id+1],tree[2*id+2]);
}
vector<ll> tobrute;
void solve(){
	cin >>n;
	ll q;
	cin >>q;
	tobrute.resize(n);
	vector<int> vec(n);
	for(int i=0;i<=4*n;i++){
		lazy[i]=neutral;
		tree[i].clear();
		has_lazy[i]=false;
	}
	for(int i=0;i<n;i++){
		cin>>vec[i];
		update1(i,vec[i]);
	}
	for(int i=0;i<q;i++){
		int qq;
		cin >> qq;
		if(qq==1){
			int l,r,x;
			cin >> l >> r >> x;
			l--;r--;
			update2(l,r,x);

		}else if(qq==2){
			int x;
			int l;
			cin >>l;
			l--;
			cin >>x;
			update1(l,x);
		}else{
			int l,r;
			cin >> l >> r;
			l--;r--;
			cout << get(l,r).getmax()<<'\n';

		}
	}
	
}
	
	

 
int main() {
	fastInp;
	//init();
	//debug() << imie(s);
	//freopen("grids.in","r",stdin);
	//freopen("res.out","w",stdout);
	// __gcd <long long> (x, y);
	int tc=1;

	cin >> tc;
	//cout << setprecision(10)<<fixed;

	while(tc--){
		//i++;
		//cout <<"Test " << i << ":" << "\n";
		
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
