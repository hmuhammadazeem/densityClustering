#pragma once
#include "NodeClass.h"

class myNode {
public:
	hNode* data;
	myNode* next;

	myNode() {
		next = NULL;
	}
};

class myList {
public:
	myNode* head;
	int n;

	myList();
	~myList();

	void push(hNode* p);
	void deqeue();

	hNode* top();

	void MergeSort(myNode*& headRef);
	myNode* SortedMerge(myNode*& a, myNode*& b);
	void FrontBackSplit(myNode*& source, myNode*& frontRef, myNode*& backRef);
};