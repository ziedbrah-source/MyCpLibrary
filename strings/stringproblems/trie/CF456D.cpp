// WE ARE NOT HERE TO TAKE PART , WE ARE HERE TO TAKE OVER
#include <bits/stdc++.h>
using namespace std;
#define fastInp cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
typedef long long ll;
typedef long double ld;
ll n,q,d;
// problem: https://codeforces.com/contest/456/problem/D
struct vertex{
	char alphabet;
	bool exists;
	vertex* child[26];
	vertex(char a): alphabet(a),exists(false) {
		for(int i=0;i<26;i++){
			child[i]=NULL;
		}
	}

};
class trie{
	public: 
	vertex* root;
	vertex* currr;
	trie(){
		root=new vertex('!');
		currr=root;
	}
	void insert(string word){
		vertex* curr=root;
		for(int i=0;i<(int)word.size();i++){
			int alphaNum=word[i]-'a';
			if(curr->child[alphaNum]==NULL){
				curr->child[alphaNum]=new vertex(word[i]);
			}
			
			curr=curr->child[alphaNum];
			curr->exists=true;
		}
		curr->exists=true;
	}
	pair<bool,bool> start(){
		bool t=firstwin(currr);
		bool t2=false;
		for(int i=0;i<26;i++){
			if(currr->child[i]==NULL)continue;
			t2|=firstlose(currr->child[i]);
		}
		return {t,t2};
 
	}
	// ena ki nakhtar haja , lekher 3omrou mayekhser
	int cnt=0;
	bool firstlose(vertex* start){
		cnt++;
		bool t=false;
		bool ttt=true;
		int cntt=0;
		for(int i=0;i<26;i++){
			if(start->child[i]!=NULL){
				cntt++;
				bool tt=firstlose(start->child[i]);
				ttt=ttt&(!tt);
				
				
			}

		}
		if(cntt){
			return ttt;
		}
		cnt--;
		return t;
	}


	bool firstwin(vertex* start){
		bool t=false;
		for(int i=0;i<26;i++){
			if(start->child[i]!=NULL){
				t|=!firstwin(start->child[i]);
			}
			
		}
		return t;
	}
	
};
void solve(){
	trie t;
	ll k;
	cin >> n >>k ;
	for(int i=0;i<n;i++){
		string str;
		cin >> str;
		t.insert(str);
	}
	pair<bool,bool> bl=t.start();
	bool tr=bl.first;

	if(tr&&bl.second){
		cout <<"First"<<"\n";
		return;
	}
	if(!tr){
		cout << "Second"<<'\n';
		return;
	}
	if(k%2==1){
		cout <<"First"<<'\n';
	}else{
		cout <<"Second"<<'\n';
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



