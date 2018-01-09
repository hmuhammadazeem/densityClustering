/*
#	Implementation of Graph class member functions.
#	Dev		   :	 Muhammad Azeem
*/


//Interface of Graph class
#include "Graph.h"


Graph::Graph() {
	headV = NULL;
};

Graph::~Graph() {
	vNode* temp;
	while (headV != NULL) {
		temp = headV;
		headV = headV->next;
		delete temp;
	}
	temp = NULL;
}

//Public member functions

//Add new vertex
vNode* Graph::addtoList(std::string Name) {
	vNode* _new = new vNode();
	_new->name = Name;

	if (headV == NULL) {
		headV = _new;
		return _new;
	}
	else {
		vNode* temp = headV;
		_new->next = temp;
		headV = _new;
		return _new;
	}
}

//Create edge function
void Graph::addEdge(vNode* dest, vNode* src, double sweight) {
	dest->insertNode(src, sweight);  //Insert node is function of vNode class present in NodeClass.h
	src->insertNode(dest, sweight); //
}

//Simple function that outputs the whole graph as an adjacency list to a file.
void Graph::Print(std::ofstream *file) {
	vNode* temp = headV;
	hNode* t = temp->adjNodes;

	while (temp != NULL) {
		t = temp->adjNodes;
		*file << temp->name << " " << " " << temp->nodeWeight << " ";
		while (t != NULL) {
			*file << " -> " << t->name << " " << t->edgeWeight << " ";
			t = t->hNext;
		}
		*file << " " << std::endl;
		temp = temp->next;
	}
}

//Find the highest degree node that is not already in some cluster
//Simple traversal used because the adjacency list is sorted in decending order
void Graph::generateHighest() {
	vNode* temp = headV;

	while (temp != NULL) {
		if (temp->inCluster == false && temp->clusterNumber == -1) {
			break;
		}
		temp = temp->next;
	}
	highest = temp;
}


//Merge Sort implementation
void Graph::MergeSort(vNode*& headRef)
{
	vNode* head = headRef;
	vNode* a;
	vNode* b;

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

vNode* Graph::SortedMerge(vNode*& a, vNode*& b)
{
	vNode* result = NULL;

	/* Base cases */
	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);

	/* Pick either a or b, and recur */
	if (a->nodeWeight > b->nodeWeight)
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
void Graph::FrontBackSplit(vNode*& source, vNode*& frontRef, vNode*& backRef)
{
	vNode* fast = NULL;
	vNode* slow = NULL;
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