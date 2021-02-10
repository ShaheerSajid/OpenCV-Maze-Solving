#include "List.h"
using namespace std;

Linkedlist::Linkedlist()
{
	head = new listNode;
	head->data = 0;
	head->next = NULL;
}

void Linkedlist::appendNodeEnd(float a)
{
	listNode *newNode;
	listNode *nodeptr;

	newNode = new listNode;
	newNode->data = a;
	newNode->next = NULL;

	if (head == NULL)
		head = newNode;
	else
	{
		nodeptr = head;
		while (nodeptr->next)
			nodeptr = nodeptr->next;
		nodeptr->next = newNode;
	}
}

void Linkedlist::appendNodeBeginning(float a)
{
	listNode *newNode;

	newNode = new listNode;
	newNode->data = a;
	newNode->next = head->next;
	head->next = newNode;




}
void Linkedlist::appendNodeAt(int loc, float num)
{
	if (loc == 0)
		Linkedlist::appendNodeBeginning(num);
	else
	{
		listNode *newNode;
		newNode = new listNode;
		newNode->data = num;

		listNode *nodeptr;
		nodeptr = head;
		for (int i = 0; i < loc; i++)
			nodeptr = nodeptr->next;
		newNode->next = nodeptr->next;
		nodeptr->next = newNode;



	}
}
void Linkedlist::deleteNodeAt(int a)
{
	listNode *nodePtr, *previousNode = NULL;
	if (!head)
		return;
	if (a == 0) {
		nodePtr = head->next;
		head->next = nodePtr->next;
		delete nodePtr;
	}
	else {

		nodePtr = head;
		for (int i = 0; i < a; i++)
		{
			previousNode = nodePtr;
			nodePtr = nodePtr->next;
		}

		previousNode->next = nodePtr->next;
		delete nodePtr;
	}
}

void Linkedlist::printList()
{

	listNode *nodePtr;
	nodePtr = head;
	nodePtr = nodePtr->next;
	int count = 1;
	while (nodePtr)
	{
		cout << count << " : " << nodePtr->data << endl;
		nodePtr = nodePtr->next;
		count++;
	}
	
}

int Linkedlist::getData(int a)
{
	listNode *nodePtr;
	if (a == 0) return head->next->data;
	nodePtr = head->next;
	for (int i = 0; i < a; i++)
		nodePtr = nodePtr->next;
	return nodePtr->data;
}
int Linkedlist::counter()
{
	listNode *nodePtr;
	nodePtr = head;
	int count = 1;
	while (nodePtr)
	{
		nodePtr = nodePtr->next;
		count++;
	}
	return count;
}
void Linkedlist::deleteList()
{
	
}


