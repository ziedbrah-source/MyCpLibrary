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

// basically howa chnowa el afkar, howa ennou fi kol prefix andek seg tree mou3ayna tnejem tekhou maaloumet al 
// prefix w baad tnahi menou fazet kima tnejem tnahi menou hajet etc :)
// problem: https://www.spoj.com/problems/DQUERY/  // get distinct elements number from l to r;
struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

Vertex* build(int tl, int tr) {
    if (tl == tr)
        return new Vertex(0);
    int tm = (tl + tr) / 2;
    return new Vertex(build(tl, tm), build(tm+1, tr));
}


int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos) {
    if (tl == tr)
        return new Vertex(v->sum+1);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos));
}

int query(Vertex* v,int tl,int tr,int l,int r){
	if(r<tl || l>tr){
		return 0;
	}
	if(tl>=l && tr<=r){
		return v->sum;
	}
	int tm=(tl+tr)/2;
	return query(v->l,tl,tm,l,r)+query(v->r,tm+1,tr,l,r);
}
const int MAX_VALUE=1e6+5; // the size of the ranges
// it's basically from each r we have a seg tree that can give us how many values we have from l to r (it's a sum seg tree w khw!)
int tl = 0, tr = MAX_VALUE + 1;

void solve(){
	
	vector<Vertex*> roots;
	cin >>n;
	vector<ll> vec(n);
	map<ll,ll> lasttime;
	vector<ll> a(n);
	for(int i=0;i<n;i++){
		cin >> vec[i];
		a[i]=lasttime[vec[i]];
		lasttime[vec[i]]=i+1;

	}
	roots.push_back(build(tl, tr));
	
	
	for (int i = 0; i < a.size(); i++) {
	
	    roots.push_back(update(roots.back(), tl, tr, a[i]));
	
	}

	ll q;
	cin >> q;
		debug() << imie("here") imie(q);
	for(int i=0;i<q;i++){
		ll l,r;
		cin >> l >>r;
		//l--;r--;
		cout << query(roots[r],tl,tr,0,l-1)-l+1<<'\n';
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

