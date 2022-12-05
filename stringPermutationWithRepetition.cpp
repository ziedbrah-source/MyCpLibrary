#include <bits/stdc++.h>
string input;
vector<string> vec;
map<char,int> calc;
void stringPerm(int length,string str){
	if(length==(int)input.length()){
		vec.push_back(str);
		return;
	}
	for (auto x : calc) {
		if(x.second==0){
			continue;
		}
		calc[x.first]--;
		stringPerm(length+1,str+x.first);
		calc[x.first]++;
	}
	
}
void solve(){
	cin >> input;
	int k ;
	cin >> k; // getting the k'th least lexico string :)
	for(int i=0;i<(int)input.length();i++){
		calc[input[i]]++;
		}
	stringPerm(0,"");
	sort(vec.begin(),vec.end());
	cout << vec[--k] << endl;

	
	
}
int main()
{
	
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
		solve();
    return 0;
}
