// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);

typedef long long ll;
typedef long double ld;
ll n,q,d;
// problem: https://codeforces.com/problemset/problem/706/D
// binary tree and max xor.
ll INF=2e18;
struct vertex{
	int alphabet;
	bool exists;
	int counter;
	vector<vertex*> childs;
	vertex(int a){
		alphabet=a;
		counter=0;
		childs.assign(2,NULL);
	}
};


class trie{
	public:
	vertex *root;
	trie(){
		root=new vertex(0);
	}
	void insert(int number){
		vertex* curr=root;
		for(int i=30;i>=0;i--){
			if(number&(1<<i)){
				if(curr->childs[1]==NULL){
					curr->childs[1]=new vertex(1);
				}
				curr=curr->childs[1];
				curr->counter++;
			}else{
				if(curr->childs[0]==NULL){
					curr->childs[0]=new vertex(0);
				}
				curr=curr->childs[0];
				curr->counter++;
			}
		}
	}

	void deletev(int number){
		vertex* curr=root;
		for(int i=30;i>=0;i--){
			if(number&(1<<i)){
				
				curr=curr->childs[1];
				curr->counter--;
			}else{
				curr=curr->childs[0];
				curr->counter--;
			}
		}		
	}

	ll query(int number){
		vertex* curr=root;
		ll v=0;
		for(int i=30;i>=0;i--){
			if(number&(1<<i)){
				if(curr->childs[0]==NULL||curr->childs[0]->counter==0){
					curr=curr->childs[1];
				}else{
					curr=curr->childs[0];
					v+=(1<<i);
				}
				
			}else{
				if(curr->childs[1]==NULL||curr->childs[1]->counter==0){
					curr=curr->childs[0];
				}else{
					curr=curr->childs[1];
					v+=(1<<i);
				}			
			}
		}			
		return v;
	}


};
void solve(){
	cin >> n;
	trie t;
	t.insert(0);

	for(int i=0;i<n;i++){
		char tp;
		int v;
		cin >> tp >> v;
		if(tp=='+'){
			t.insert(v);
		}else if(tp=='?'){
			cout << t.query(v)<<'\n';
		}else{
			t.deletev(v);
		}
	}
	
}
	
	

 
int main() {
	fastInp;
	int tc=1;
	while(tc--){
		//i++;
		//cout <<"Test " << i << ":" << "\n";
		
		solve();
		
	}

	return 0;
}



