/*
#	This class is the base for the Graphs to be used in this project.
#	Dev        :	 Muhammad Azeem
*/

#include "NodeClass.h"

//hNode implementations

void hNode::markCluster(int n) {
	*clusterNumber = n;
	*inCluster = true;
}

void hNode::unMark() {
	*clusterNumber = -1;
	*inCluster = false;
}

hNode::hNode() {
	hNext = NULL;
	name = '\0';
}


//vNode implementations

void vNode::markCluster(int n) {
	clusterNumber = n;
	inCluster = true;
}

void vNode::unMark() {
	clusterNumber = -1;
	inCluster = false;
}

//Constructor
vNode::vNode() {
	nodeWeight = 0;
	next = NULL;
	adjNodes = NULL;
	neighbours = "";
	clusterNumber = -1;
	inCluster = false;
	inNeighbours = false;
	degree = 0;
	name = '\0';
}

void vNode::insertNode(vNode* a, double sweight) {

	hNode* _new = new hNode();
	_new->name = a->name;

	//Pointer to neighbours of the node
	_new->adjNodes = &a->adjNodes;

	//Node weight = sum of all the edge weights of node;
	this->nodeWeight += sweight;

	_new->nodeWeight = &a->nodeWeight;

	//neighbours: A string containing name of all the neighbours for easy searching
	this->neighbours += a->name;

	_new->edgeWeight = sweight;

	_new->neighbours = &a->neighbours;

	//Cluster checks
	_new->clusterNumber = &a->clusterNumber;
	_new->inCluster = &a->inCluster;
	_new->inNeighbours = &a->inNeighbours;

	this->degree++;
	_new->degree = &a->degree;

	if (adjNodes == NULL)
		adjNodes = _new;
	else {
		hNode* temp = adjNodes;
		_new->hNext = temp;
		adjNodes = _new;
	}
}