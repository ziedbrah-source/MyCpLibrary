struct xorBasis {
    // it's about xor on subset
    // basically you enter a whole segment of numbers and now you can answer many questions on it
    // like the k'th maximum xor you can get with any subset in the numbers that you entered
    // how many distinct subset xor you can create
    // what is the maximum xor value that you can get etc
    // you can see if you can do value X with a subset of numbers you entered!
    // the idea is to make a base with that base you check if you can construct X or smth like that, it's linear algebra!
    // cool problem: https://codeforces.com/group/Rilx5irOux/contest/538817/problem/H -> you can query on [l,r] and check some caractersics from that l,r with the merge of seg tree! ..
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

xorBasis merge(xorBasis b1,xorBasis b2){
    vector<int> vv=b2.givevalues();
    for(auto el:vv){
        b1.addVector(el);
    }
    return b1;
}