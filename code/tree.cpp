#include <iostream>
#include <string>
#include "tree.h"
using namespace std;


Tree::Tree(olist a)
{
	root = new node;
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	root->data = a;
	rootexist = true;

}

void Tree::recursiveInsert(olist a)
{
	node *ptr;
	if (!rootexist)
	{
		root = new node;
		root->parent = NULL;
		root->left = NULL;
		root->right = NULL;
		root->data = a;
		rootexist = true;
	}
	ptr = root;
	insert(a, ptr);
}

void Tree::insert(olist a, node *ptr)
{

	if (a < ptr->data)
	{
		if (ptr->left == NULL)
		{
			node *n = new node;
			n->left = NULL;
			n->right = NULL;
			n->parent = ptr;
			n->data = a;
			ptr->left = n;
			return;
		}
		else insert(a, ptr->left);
	}


	else if (a > ptr->data)
	{
		if (ptr->right == NULL && ptr->left != NULL)
		{
			node *n = new node;
			n->left = NULL;
			n->right = NULL;
			n->parent = ptr;
			n->data = a;
			ptr->right = n;
			return;
		}
		else if (ptr->right == NULL && ptr->left == NULL)
		{
			node *n = new node;
			olist t = ptr->data;
			ptr->data = a;
			n->left = NULL;
			n->right = NULL;
			n->parent = ptr;
			n->data = t;
			ptr->left = n;
			return;
		}

		else insert(a, ptr->right);
	}
	else return;




}

void Tree::recursivePrint()
{
	node *ptr = root;
	print(ptr, true);
}
void Tree::print(node *ptr, bool state)
{

	if (ptr == NULL) return;
	node *p = NULL;
	if (ptr->parent == NULL) p = ptr;
	else p = ptr->parent;
	string x = state ? "RIGHT" : "LEFT";
	if (ptr == root) x = "ROOT";
	cout << ptr->data.second.first << "," << ptr->data.second.second << " " << x << " of " << p->data.second.first << "," << p->data.second.second << endl;
	print(ptr->left, false);
	print(ptr->right, true);

}

olist Tree::erase()
{
	node *p, *q;
	p = root;
	olist x;
	if (p->left == NULL && p->right == NULL)
	{
		x = p->data;
		root = NULL;
		rootexist = false;
		return x;
	}
	if (p->left == NULL)
		p = p->right;

    while (p->left != NULL)
		p = p->left;
	
	if (p->parent->right == NULL)
	{
		x = p->data;
		p->parent->left = NULL;
		free(p);
	}
	else if (p->parent->right != NULL)
	{
		x = p->data;
		p->data = p->parent->data;
		p->parent->data = p->parent->right->data;
		p->parent->right = NULL;
		free(p->parent->right);
	}
	return x;
}


bool Tree::empty()
{
	if (!rootexist) return 1;
	else return 0;
}