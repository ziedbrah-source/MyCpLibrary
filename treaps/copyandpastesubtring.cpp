#include <bits/stdc++.h>
using namespace std;
/*
problem: 
    Given a string, your task is to process operations where you cut a substring and paste it to the end of the string. What is the final string after all the operations?
    Input
    The first input line has two integers n and m: the length of the string and the number of operations. The characters of the string are numbered 1,2,\dots,n.
    The next line has a string of length n that consists of characters A–Z.
    Finally, there are m lines that describe the operations. Each line has two integers a and b: you cut a substring from position a to position b.
    Output
    Print the final string after all the operations.
    Constraints

    1  n, m <=2 * 10^5
    1  a  and b <= n

    Example
    Input:
    7 2
    AYBABTU
    3 5
    3 5

    Output:
    AYABTUB

Solution: 
    We will use implicit treaps to represent the array. For each operation, divide
    it into two phases: cut and paste. For the cut phase, we split the array into
    three parts: 
    [1, a) , [a, b] , and (b, n]
    . This can be accomplished using
    two split operations. For the paste phase, we can rearrange the sections such
    that we merge them in the order 
    [1, a),(b, n],[a, b]. This can be done
    using two merge operations.

*/  

struct Node {
	char val;
	int weight, size;
	Node *left, *right;
	Node(char c) : val(c), weight(rand()), size(1), left(NULL), right(NULL) {}
} *root;

inline int size(Node *treap) { return treap ? treap->size : 0; }

void split(Node *treap, Node *&left, Node *&right, int val) {
	if (!treap) {
		left = right = NULL;
		return;
	}

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

	if (left->weight < right->weight) {
		merge(left->right, left->right, right);
		treap = left;
	} else {
		merge(right->left, left, right->left);
		treap = right;
	}
	treap->size = 1 + size(treap->left) + size(treap->right);
}

void go(Node *n){
    if(!n) return;
    go(n->left);
    cout <<n->val;
    go(n->right);
    return;
}
int main() {
	int N, Q;
	string S;

	cin >> N >> Q >> S;
	for (char c : S) { merge(root, root, new Node(c)); }
	while (Q--) {
		int l, r;
		cin >> l >> r;
		Node *a, *b, *c, *d;
		split(root, a, b, l - 1);
		split(b, c, d, r - l + 1);
		merge(root, a, d);
		merge(root, root, c);
	}
    go(root);
    cout <<'\n';
	
}