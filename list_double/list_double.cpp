#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int data = 1000;
	Node *next = NULL;
	Node *pre = NULL;
};

Node * reverseList_recursive(Node *head)
{

}

void displayList(Node *head)
{
	printf("display begin!!\n");
	Node *pnow = head;
	while(pnow != NULL)
	{
		printf("current data: %d\n",pnow->data);
		pnow = pnow->next;
	}
	printf("display finished!!\n");
}

int main()
{
	Node *head = (Node *)malloc(sizeof(Node));
	head->data = 1;

	Node *tail = (Node *)malloc(sizeof(Node));
	tail->data = 2000;
	head->next = tail;

	Node *pnow = head;
	Node *pnext = NULL;

	for(int i = 1;i < 10;++i)
	{
		pnext = pnow->next; // store next ptr
		Node *mid = (Node *)malloc(sizeof(Node));
		mid->data = i + head->data;
		mid->next = pnext;
		pnow->next = mid;
		pnow = mid; // move pnow forward
	}

	displayList(head);

	head = reverseList(head);

	displayList(head);

    return 0;
}
