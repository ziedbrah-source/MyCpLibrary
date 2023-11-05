#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;


const ll MOD = 998244353;
ll INF=2e18;
#define SIZE 11111+1

int P[SIZE * 2];
string convertToNewString(const string &s) {
    string newString = "@";

    for (int i = 0; i < s.size(); i++) {
        newString += "#" + s.substr(i, 1);
    }

    newString += "#$";
    return newString;
}
string s="";
/*
[s: qu]  [Q: @#q#u#$] 
0 @ 0 # 1 q 0 # 1 u 0 # 0 $ 
//  in P for each position in Q , in P[ that position] you have the longest substring , in wichi you are in the center, so if Q[i]=="#" you are having an even substring
if you are in smth not ="#" you are in an odd substring
you need to ignore first and last value in P as it's for @ and $ (zero all the time for implementation purposes)
*/
void manacher(string &s){
       
        string Q = convertToNewString(s);
        for(int i=0;i<=(int)Q.size();i++) P[i]=0;
    int c = 0, r = 0;                // current center, right limit

    for (int i = 1; i < Q.size() - 1; i++) {
        // find the corresponding letter in the palidrome subString
        int iMirror = c - (i - c);

        if(r > i) {
            P[i] = min(r - i, P[iMirror]);
        }

        // expanding around center i
        while (Q[i + 1 + P[i]] == Q[i - 1 - P[i]]){
            P[i]++;
        }

        // Update c,r in case if the palindrome centered at i expands past r,
        if (i + P[i] > r) {
            c = i;              // next center = i
            r = i + P[i];
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
	//debug() << imie(sieve);
//	cin >> tc;
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


