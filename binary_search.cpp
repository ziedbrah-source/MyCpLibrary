bool check(int q){
// check function;
}

/// TTTTTTTTTTFFFFFFFF
int l=-1;
int r=k+1;
// k+1 dima False (invariant;
// l=-1 tnejem tbadelha ama nejmou nhotoha =0 mathalan el
// lehné khtarna =-1 bech ken matbadletech naarfou eli mafama hata solution ! 
while(l<r){
	int mid=l+(r-l+1)/2;	
	if(check(mid)){
			//cout << mid << endl;
			l=mid;
		}else{
			r=mid-1;
		}
}
// another implem from usaco : 
int last_true(int lo, int hi) {
	lo--;
	while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;
		if (check(mid)) {
			lo = mid;
		} else {
			hi = mid - 1;
		}
	}
	return lo;
}



///FFFFFFFTTTTTTTT
	int l=0; // faux;
	int r=n; // vrai >> invariant :)

	while(l<r){
		int mid=l+(r-l)/2;
		
		if(check(mid)){
			
			r=mid;
		}else{
			l=mid+1;
		}
	}
	
	cout << r << "\n";
	
////////////////////////
binary search on real values:
const double EPS = 1e-7;

bool check(double r){}
double lo = 0.0, hi = 10000000000000000.0;
while (fabs(hi-lo) > EPS) {
	// answer is not found yet
		double mid = (lo+hi) / 2.0;
	// try the middle value
		check(mid) ? hi = mid : lo = mid;
}












