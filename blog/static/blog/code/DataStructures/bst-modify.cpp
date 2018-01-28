#include<iostream>
using namespace std;
struct node {
	double val;
	node* left;
	node* right;
	node* parent;//need this pointer for successor/predecessor
	node(double v):val(v),left(NULL),right(NULL), parent(NULL){}
	void addLeft(node* n) {
		left = n;
		n->parent = this;
	}
	void addRight(node* n) {
		right = n;
		n->parent = this;
	}
};

//search in the tree for value: v
node* search(node* root, double v) {
	if (root)
		cout<<root->val<<" -> ";
	if (!root || root->val == v)
		return root;
	else if (root->val > v) 
		return search(root->left, v);
	else 
		return search(root->right, v);
}
//search for maximum node in the subtree rooted by root
node* max(node* root) {
	node* p=root;
	while (root) {
		p = root;
		root = root->right; 
	}
	return p;
}

//search for minimum node in the subtree rooted by root
node* min(node* root) {
	node* p=root;
	while (root) {
		p = root;
		root = root->left; 
	}
	return p;
}
// predecessor, the largest node that is smaller than root 
node* predecessor(node* root) {
	if (root) {
		if (root->left)
			return max(root->left);
		else {
			node* p = root->parent;
			while (p && root == p->left) {
				root = p;
				p = p->parent;
			}
			return p;
		}
	}
	else 
		return root;

}

// successor, the smallest node that is larger than root 
node* successor(node* root) {
	if (root) {
		if (root->right)
			return min(root->right);
		else {
			node* p = root->parent;
			while (p && root == p->right) {
				root = p;
				p = p->parent;
			}
			return p;
		}
	}
	else 
		return root;
}
int main(int argn, char** argv) {
	//build an example binary search tree
	node* root = new node(9);
	root->addLeft( new node(7) );
	root->addRight( new node(14) );
	root->left->addLeft( new node(4) );
	root->left->left->addLeft( new node(1) );
	root->left->left->addRight( new node(6)) ;
	root->right->addLeft( new node(10) );
	root->right->addRight( new node(15) );
	root->right->left->addRight( new node(11) );

	double v = 11;
	cout<<"Search for "<<v<<endl;
	cout<<"Path: ";
	node* n = search(root, v);
	if (n)
		cout<<"Success !"<<endl;
	else
		cout<<"Failed !"<<endl;

	node* nMin = min(root);
	cout<<"Minimum value in the tree: "<<nMin->val<<endl;

	node* nMax = max(root);
	cout<<"Maximum value in the tree: "<<nMax->val<<endl;

	n = root->left->left->right;
	node* sn = successor(n);
	cout<<n->val<<"'s successor: "<<sn->val<<endl;

	n = root->right;
	node* pn = predecessor(n);
	cout<<n->val<<"'s predecessor: "<<pn->val<<endl;
	return 0;
}
