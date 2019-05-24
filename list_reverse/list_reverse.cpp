#include <bits/stdc++.h>

using namespace std;

struct Node
{
	int data = 1000;
	Node *next = NULL;
};

// typedef struct Node{
//     int data;
//     Node *next;
// } Node, *List;

Node * reverseList(Node *head)
{
	Node *pnow = head; // current node ptr
	Node *pre = NULL; // node before current ptr
	Node *pnext = NULL; // node next ptr

	Node *tail = head; // tail ptr // special consideration for one node list or empty list

	while(pnow != NULL)
	{
		pnext = pnow->next; // save next ptr
		if(pnext == NULL) 
		{
			tail = pnow;
			// break; // wrong !!! the list will break at tail
		}
		pnow->next = pre;

		pre = pnow;
		pnow = pnext;

	}

	return tail;
}

Node * reverseList_recursive(Node *head)
{
	if(head == NULL || head->next == NULL)
	{
		return head;
	}
	else
	{
		Node *newhead = reverseList_recursive(head->next); // first go to the end of list
		// now newhead -> last node, head is 2nd to last node
		head->next->next = head;
		head->next = NULL;

		return newhead;
	}
}

// ****************** local reverse ********************

// inner function for local_reverseList
void local_reverse(Node *start, Node *end)
{
	Node *pnow = start->next; // current node ptr
	Node *pre = start; // node before current ptr
	Node *pnext = NULL; // node next ptr

	Node *tail = end->next; // tail ptr

	if(pnow == end)
	{
		pnow->next = start;
		start->next = tail;
	}
	else{

		while(1)
		{
			// std::cout << "pnow: " << pnow->data <<std::endl;
			// std::cout << "end->next: " << end->next->data<<std::endl;

			pnext = pnow->next; // save next ptr
			pnow->next = pre;

			pre = pnow;
			pnow = pnext;

			if(pnow == tail)
			{
				start->next = tail;
				break;
			}

		}
	}
}

Node * local_reverse_recursive(Node *start, Node *tail)
{
	if(start->next == tail)
	{
		return start;
	}
	else
	{
		Node* newhead = local_reverse_recursive(start->next,tail);
		start->next->next = start;
		start->next = tail;

		// std::cout << "start: " << start->data << std::endl;
		return newhead;
	}
}

// reverse list from m to n (index starts from 1)
Node * local_reverseList(Node *head, int m, int n)
{
	if(head == NULL)
	{
		std::cout << "NULL list !!!" << std::endl;
		return head;
	}

	else if(m == n)
	{
		std::cout << "m==n !!!" << std::endl;
		return head;
	}

	else
	{
		// get node at sort start - 1
		Node *pre = (Node *)malloc(sizeof(Node));
		pre->next = head;

		for(int i = 0;i < m-1;++i)
		{
			pre = pre->next;
		}

		// get node at sort end
		Node *end = pre->next;

		for(int i = m;i < n;++i)
		{
			end = end->next;
		}

		printf("pre next %d\n", pre->next->data);
		printf("end %d\n", end->data);

		// local_reverse(pre->next,end);
		// pre->next = end;

		Node *tail = end->next;
		Node *newhead = local_reverse_recursive(pre->next,tail);
		std::cout << "newhead: " << newhead->data << std::endl;
		pre->next = newhead;

		if(m == 1)
		{
			return newhead;
		}
		else
		{
			return head;
		}
	}

}

// ******************** display ******************

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

	//************* reverse functions *************
	// head = reverseList(head);
	// head = reverseList_recursive(head);
	head = local_reverseList(head,1,7);

	displayList(head);

    return 0;
}
