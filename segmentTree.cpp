#include <bits/stdc++.h>
using namespace std;
vector<int> vec;
vector<long long> tree;
// build the tree :') 
int n,q;
int firstN;
void buildTree(){
	for(int i=0;i<n;i++){
		tree[n+i]=vec[i];
	}
	// calculate the sum : 
	for(int i=n-1;i>=1;i--){
		tree[i]=tree[2*i]+tree[2*i+1];
	}
}
long long getSum(int node,int node_low,int node_high,int query_low,int query_high){
	if(node_high<=query_high && node_low>=query_low){
		return tree[node];
	}
	if(node_low>query_high || node_high<query_low){
		return 0;
	}
	int mid=(node_low+node_high)/2;
	return getSum(2*node,node_low,mid,query_low,query_high)+getSum(2*node+1,mid+1,node_high,query_low,query_high);
}
void change(int index,int val){
	tree[n+index]=val;
	for(int j=(n+index)/2;j>=1;j/=2){
		tree[j]=tree[2*j]+tree[2*j+1];
	}
}

void solve(){
	cin >> n >>q ;
	firstN=n;
	vec.resize(n);
	for(int i=0;i<n;i++){
		cin>> vec[i];
	}
	while(__builtin_popcount(n)!=1){
		vec.push_back(0);
		n++;
	}
	// 2*n but actually we need 2*n-1 but with this implementation we start at tree[1] as a root, so we will sizeit as 2*n;
	
	tree.resize(2*n);
	buildTree();
	while(q--){
		int type;
		cin >> type;
		if(type==1){
			int pos;
			int val;
			cin >> pos >> val;
			change(--pos,val);
			
		}else{
			int low, high;
			cin >> low >> high;
			low--;
			high--;
			cout << getSum(1,0,n-1,low,high) <<endl;
		}
	}
	
}
int main()
{
	
	// Use standard input to read from "paint.in"
	//freopen("perimeter.in", "r", stdin);
	// Use standard output to write to "paint.out"
	//freopen("perimeter.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//int tc;
	//cin >> tc;
	//while(tc--){
    //while(scanf("%d %d",&m,&n)!=EOF)
		solve();
	
	//}
    return 0;
}
