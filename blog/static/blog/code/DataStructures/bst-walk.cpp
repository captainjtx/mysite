#include<iostream>
using namespace std;
struct node{
	double val;
	node* left;
	node* right;
	node(double v):val(v),left(NULL),right(NULL){}
};

void inorder(node* root)
{
	if(!root)
		return;
	inorder(root->left);
	cout<<root->val<<" ";
	inorder(root->right);
}

void preorder(node* root)
{
	if(!root)
		return;
	cout<<root->val<<" ";
	preorder(root->left);
	preorder(root->right);
}

void postorder(node* root)
{
	if(root)
	{
		postorder(root->left);
		postorder(root->right);
		cout<<root->val<<" ";
	}
}

int main(int argn,char** argv) {
	//build an example binary search tree
	node* root=new node(9);
	root->left=new node(7);
	root->right=new node(14);
	root->left->left=new node(4);
	root->left->left->left=new node(1);
	root->left->left->right=new node(6);
	root->right->left=new node(10);
	root->right->right=new node(15);
	root->right->left->right=new node(11);

	cout<<"Inorder tree walk: ";
	inorder(root);
	cout<<endl;
	cout<<"Preorder tree walk: ";
	preorder(root);
	cout<<endl;
	cout<<"Postorder tree walk: ";
	postorder(root);
	cout<<endl;
	return 0;
}
