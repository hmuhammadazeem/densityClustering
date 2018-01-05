#pragma once
//File stream library
#include "NodeClass.h"
#include <fstream>


class Graph {
public:
	vNode* headV;
	vNode* highest;
	int n;

	/* Contructor */
	Graph();
	/* Destructor */
	~Graph();
	
	
	//Add new vertex to graph
	vNode* addtoList(std::string Name);

	//Create edge function
	void addEdge(vNode* dest, vNode* src, double sweight);

	//Simple function that outputs the whole graph as an adjacency list to a file.
	void Print(std::ofstream *file);

	//Highest waited node generate
	void generateHighest();

	
	//Merge Sort and it's utility functions
	void MergeSort(vNode*& headRef);
	void FrontBackSplit(vNode*& source, vNode*& frontRef, vNode*& backRef);
	vNode* SortedMerge(vNode*& a, vNode*& b);


	void sort_list(vNode* list);

	

};