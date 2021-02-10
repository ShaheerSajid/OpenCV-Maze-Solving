#include <iostream>

class Linkedlist
{
public:
	struct listNode
	{
		float data;
		struct listNode* next;
	};
	listNode *head;

	Linkedlist();

	void appendNodeBeginning(float);
	void appendNodeEnd(float);
	void appendNodeAt(int, float);
	void deleteNodeAt(int);
	void printList();
	void deleteList();
	int getData(int);
	int counter();

};
