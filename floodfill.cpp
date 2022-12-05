#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef vector<int> vi;

#define mp make_pair
#define pb push_back

#define FOR(i, a, b) for (int i=a; i<b; i++)
#define F0R(i, a) for (int i=0; i<a; i++)

#define f first
#define s second
#define lb lower_bound
#define ub upper_bound

const int MOD = 1000000007;
double PI = 4*atan(1);
/*
// how to sort+ use the iterator:)
	std::sort(v.begin(), v.end(), std::greater<int>());
  
    std::vector<int>::iterator low, up;
    low = std::lower_bound(v.begin(), v.end(), 3, std::greater<int>());         
    up = std::upper_bound(v.begin(), v.end(), 5, std::greater<int>()); 
*/

// #PREFIX SUM 1 index Based.

/*
bool comp(string s1,string s2){
	// return the one smaller lexicographically
	return s1+s2 < s2+s1;
}*/
const int maxN=1010;
char matrix[maxN][maxN];
bool visited[maxN][maxN];
int n,m;
bool validity(int x,int y){
	if(x<0 || x>=n || y<0 || y>=m){
		return false;
	}
	if(matrix[x][y]=='#'){
		return false;
	}
	if(visited[x][y]){
		return false;
	}
	return true;
}
void floodFill(int x,int y){
	if(!validity(x,y)){
		return;
	}
	visited[x][y]=true;
	floodFill(x+1,y);
	floodFill(x-1,y);
	floodFill(x,y+1);
	floodFill(x,y-1);
}
1
ICPC


1
ACMA
APCA
TOGI
NEST
void solve(){
	cin >> n >>m;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cin >> matrix[i][j];
		}
	}
	int counter=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(!visited[i][j]&&matrix[i][j]=='.'){
				counter++;
				//cout << i << " " << j <<endl;
				floodFill(i,j);
			}
		}
	}
		
		cout << counter << "\n";

	
	
	
	
	
}
int main()
{
	
	// Use standard input to read from "paint.in"
	//freopen("fenceplan.in", "r", stdin);
	// Use standard output to write to "paint.out"
	//freopen("fenceplan.out", "w", stdout);
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
