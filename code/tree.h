#include <iostream>
using namespace std;


typedef pair<int, pair<int, int>> olist;
class Tree
{

private:

	struct node
	{
		olist data;
		node *left;
		node *right;
		node *parent;
	};
	node *root;
	bool rootexist = true;

public:

	Tree(olist);
	void recursiveInsert(olist);
	void insert(olist, node*);
	olist erase();
	bool empty();
	void print(node*, bool);
	void recursivePrint();

};