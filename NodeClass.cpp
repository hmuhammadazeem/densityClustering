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

vNode::vNode() {
	nodeWeight = 0;
	next = NULL;
	adjNodes = NULL;
	clusterNumber = -1;
	inCluster = false;
	inNeighbours = false;
}

void vNode::insertNode(vNode* a, double sweight) {

	hNode* _new = new hNode();
	_new->name = a->name;

	//Pointer to neighbours of the node
	_new->adjNodes = &a->adjNodes;

	//Node weight = sum of all the edge weights of node;
	this->nodeWeight += sweight;

	_new->nodeWeight = &a->nodeWeight;

	_new->edgeWeight = sweight;

	//Cluster checks
	_new->clusterNumber = &a->clusterNumber;
	_new->inCluster = &a->inCluster;
	_new->inNeighbours = &a->inNeighbours;

	if (adjNodes == NULL)
		adjNodes = _new;
	else {
		hNode* temp = adjNodes;
		_new->hNext = temp;
		adjNodes = _new;
	}
}