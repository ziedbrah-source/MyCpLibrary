#include <bits/stdc++.h>
using namespace std;

int rand(int a,int b){
	return a+rand()%(b-a+1);
}
int main(int argc, char* argv[]) {
	srand(atoi(argv[1]));
	int n=rand(1,50000);
	int q=rand(1,20);
	cout << n << " "<< q << "\n";
	for(int i=0;i<n;i++){
		int col=rand(0,1);
		cout << col << " ";
	}
	cout << "\n";
	// this is for a tree
	for(long i = 2; i <= n; ++i) cout << (rand() % (i - 1) + 1) << " " << i << "\n";
	for(int i=0;i<q;i++){
		cout << rand(1,n) <<  "\n";
	}
	return 0;
}
