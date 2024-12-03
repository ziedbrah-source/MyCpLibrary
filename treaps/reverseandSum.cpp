#include <bits/stdc++.h>
using namespace std;
/*

Time limit: 1.00 s
Memory limit: 512 MB



Given an array of n integers, you have to process following operations:

reverse a subarray
calculate the sum of values in a subarray

Input
The first input line has two integers n and m: the size of the array and the number of operations. The array elements are numbered 1,2,\dots,n.
The next line as n integers x_1,x_2,\dots,x_n: the contents of the array.
Finally, there are m lines that describe the operations. Each line has three integers t, a and b. If t=1, you should reverse a subarray from a to b. If t=2, you should calculate the sum of values from a to b.
Output
Print the answer to each operation where t=2.
Constraints

1 1<=n <=2*10^5
1 1m<=10^5
0 x_i <= 10^9
1 a<=n && b<=n

Example
Input:
8 3
2 1 3 4 5 3 4 4
2 2 4
1 3 6
2 2 4

Output:
8
9



*/
typedef long long i64;
struct node {
	bool lz;
	int sz, we;
	i64 key, sum;
	node *lc, *rc;

	node(int k) {
		lc = rc = NULL;
		key = sum = k;
		we = rand();
		sz = 1;
		lz = 0;
	}
};


int size(node *N) { return N ? N->sz : 0; }
i64 suma(node *N) { return N ? N->sum : 0; }
bool lazy(node *N) { return N ? N->lz : 0; }

void pull(node *&N) {
	N->sz = size(N->lc) + size(N->rc) + 1;
	N->sum = suma(N->lc) + suma(N->rc) + N->key;
}

void push(node *&N) {
	if(!lazy(N)) return;
	N->lz = 0;
	swap(N->lc, N->rc);
	if(N->lc) N->lc->lz ^= 1;
	if(N->rc) N->rc->lz ^= 1;
}

node *merge(node *&root, node *L, node *R) {
	if(!L) return root = R;
	if(!R) return root = L;
	push(L);
	push(R);
	if(L->we < R->we) {
		merge(L->rc, L->rc, R);
		root = L;
	} else {
		merge(R->lc, L, R->lc);
		root = R;
	}
	pull(root);
	return root;
}

node *split(node *root, node *&L, node *&R, int L_size) {
	if(!root) return L = R = NULL;
	push(root);
	if(size(root->lc) < L_size) {
		split(root->rc, root->rc, R, L_size - size(root->lc) - 1);
		L = root;
	} else {
		split(root->lc, L, root->lc, L_size);
		R = root;
	}
	pull(root);
	return root;
}

i64 query(node *root, int pre) {
	push(root);
	if(!root || pre == 0) return 0;
	if(size(root) == pre) return suma(root);
	if(pre <= size(root->lc)) return query(root->lc, pre);
	return suma(root->lc) + query(root->rc, pre - size(root->lc) - 1) + root->key;
}

node *root, *T;
node *t1, *t2, *t3;

ostream &operator << (ostream &os, node *N) {
	if(!N) return os;
	push(N);
	os << N->lc;
	os << N->key << " ";
	os << N->rc;
	return os;
}

int main() {
	int n, q;
	cin >> n >> q;
	for(int i = 0, t; i < n; i++) {
		cin >> t;
		merge(root, root, new node(t));
	}

	while(q--) {
		int t, l, r;
		cin >> t >> l >> r;
		if(t == 1) {
			split(root, t1, T, l - 1);
			split(T, t2, t3, r - l + 1);
			t2->lz ^= 1;
			merge(root, t1, t2);
			merge(root, root, t3);
		} else {
			cout << query(root, r) - query(root, l - 1) << endl;
		}
	}
	return 0;
}