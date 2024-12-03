#include <bits/stdc++.h>
using namespace std;
/*
Given a string, your task is to process operations where you reverse a substring of the string. What is the final string after all the operations?
Input
The first input line has two integers n and m: the length of the string and the number of operations. The characters of the string are numbered 1,2,\dots,n.
The next line has a string of length n that consists of characters A–Z.
Finally, there are m lines that describe the operations. Each line has two integers a and b: you reverse a substring from position a to position b.
Output
Print the final string after all the operations.
Constraints

1 n, m <=2 * 10^5
1  a & b <= n

Example
Input:
7 2
AYBABTU
3 4
4 7

Output:
AYAUTBB


Solution:
it's implemented in reverse string function, we just put a lazy rever flag ;) and we propagate always


*/
struct Node {
	char val;
	int weight, size;
	bool rev;
	Node *left, *right;
	Node(char c) : val(c), weight(rand()), size(1), rev(false), left(NULL), right(NULL) {}
} *root;

inline int size(Node *treap) { return treap ? treap->size : 0; }
void pull(Node *&treap){
	if(treap == NULL)return;
	if(treap -> rev){
		treap -> rev = false;
		swap(treap -> left, treap -> right);
		if(treap -> left != NULL)treap -> left -> rev ^= true;
		if(treap -> right != NULL)treap -> right -> rev ^= true;
	}
}

void split(Node *treap, Node *&left, Node *&right, int val) {
	if (!treap) {
		left = right = NULL;
		return;
	}
	pull(treap);
	
	if (size(treap->left) < val) {
		split(treap->right, treap->right, right, val - size(treap->left) - 1);
		left = treap;
	} else {
		split(treap->left, left, treap->left, val);
		right = treap;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
}

void merge(Node *&treap, Node *left, Node *right) {
	if (left == NULL) {
		treap = right;
		return;
	}
	if (right == NULL) {
		treap = left;
		return;
	}
	pull(left);
	pull(right);
	if (left->weight < right->weight) {
		merge(left->right, left->right, right);
		treap = left;
	} else {
		merge(right->left, left, right->left);
		treap = right;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
}

void print(Node *root){
	if(root == NULL)return;
	pull(root);
	print(root -> left);
	cout << root -> val;
	print(root -> right);
    
	
}
void reverse_string(int l, int r){
	Node *a, *b, *c, *d; // considering 1 based indexing
	split(root, a, b, l - 1);// pointer a will be having s[1...l-1] and b will be having s[l .... n]
	split(b, c, d, r - l + 1);// pointer c will be having s[l...r] and d will be having s[r+1 .... n]
	c -> rev ^= true;
	pull(c);; // so we are intersted only in c so we reverse that lazily
	merge(b, c, d); // after reversing we merge it back
	merge(root, a, b);
	
}
int main() {
	int n,q; cin >> n >> q;
	string s; cin >> s;
	for (char &c : s) { merge(root, root, new Node(c)); }
	while (q--) {
		int l, r;
		cin >> l >> r;
		reverse_string(l,r);
	}
	print(root);
    cout <<'\n';
}