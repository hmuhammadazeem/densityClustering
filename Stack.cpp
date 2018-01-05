#include "Stack.h"
#define NULL 0

myList::myList() {
	head = NULL;
	n = 0;
}

myList::~myList() {
	myNode *p;
	while (head != NULL) {
		p = head;
		head = head->next;
		delete p;
	}
}

void myList::push(hNode* p) {
	myNode* _new = new myNode();
	_new->data = p;
	*p->inNeighbours = true;
	n++;
	if (head == NULL) {
		head = _new;
	}
	else {
		myNode* temp = head;
		head = _new;
		_new->next = temp;
	}
}

void myList::deqeue() {
	if (head == NULL)
		return;
	myNode* temp = head;
	*temp->data->inNeighbours = false;
	head = head->next;
	delete temp;
	n--;
}

hNode* myList::top() {
	if (head == NULL)
		return NULL;
	return head->data;
}

void myList::sort_list(myNode * list)
{
	myNode** heads/*[2500] = { 0 }*/;
	myNode** tails/*[2500] = { 0 }*/;

	heads = new myNode*[this->n];
	tails = new myNode*[this->n];

	for (int i = 0; i < n; i++) {
		heads[i] = 0;
		tails[i] = 0;
	}

	// O(N) loop
	for (myNode* it = list; it != 0; it = it->next) {
		myNode* next = it->next;

		if (heads[*it->data->degree] == 0) {
			heads[*it->data->degree] = it;
		}
		else {
			tails[*it->data->degree]->next = it;
		}

		tails[*it->data->degree] = it;
	}

	myNode* result = 0;

	// constant time loop
	for (size_t i = 0; i++ < this->n - 2; ) {
		if (tails[i]) {
			tails[i]->next = result;
			result = heads[i];
		}
	}
}


	void myList::MergeSort(myNode*& headRef)
	{
		myNode* head = headRef;
		myNode* a;
		myNode* b;

		/* Base case -- length 0 or 1 */
		if ((head == NULL) || (head->next == NULL))
		{
			return;
		}

		/* Split head into 'a' and 'b' sublists */
		FrontBackSplit(head, a, b);

		/* Recursively sort the sublists */
		MergeSort(a);
		MergeSort(b);

		/* answer = merge the two sorted lists together */
		headRef = SortedMerge(a, b);
	}

	myNode* myList::SortedMerge(myNode*& a, myNode*& b)
	{
		myNode* result = NULL;

		/* Base cases */
		if (a == NULL)
			return(b);
		else if (b == NULL)
			return(a);

		/* Pick either a or b, and recur */
		if (*a->data->nodeWeight > *b->data->nodeWeight)
		{
			result = a;
			result->next = SortedMerge(a->next, b);
		}
		else
		{
			result = b;
			result->next = SortedMerge(a, b->next);
		}
		return result;
	}
	void myList::FrontBackSplit(myNode*& source, myNode*& frontRef, myNode*& backRef)
	{
		myNode* fast = new myNode();
		myNode* slow = new myNode();
		if (source == NULL || source->next == NULL)
		{
			/* length < 2 cases */
			frontRef = source;
			backRef = NULL;
		}
		else
		{
			slow = source;
			fast = source->next;

			/* Advance 'fast' two nodes, and advance 'slow' one node */
			while (fast != NULL)
			{
				fast = fast->next;
				if (fast != NULL)
				{
					slow = slow->next;
					fast = fast->next;
				}
			}
		}
		/* 'slow' is before the midpoint in the list, so split it in two
		at that point. */
		frontRef = source;
		backRef = slow->next;
		slow->next = NULL;
	}