#include "ClusterClass.h"

Cluster::Cluster(double d, double cp, int t) {
	n++;
	clusterNumber = t;
	neighbours = new myList();
	threshCp = cp;
	threshDensity = d;
}

Cluster::~Cluster() {
	vNode *temp = clusterElements;
	vNode* t;
	while (temp != NULL) {
		t = temp;
		temp = temp->next;
		delete t;
	}
	delete neighbours;
}

//Member functions

//
// This function calculates number of edges of a node with the cluster.
// 
// This is used to check whether the node is in periphery of cluster.
//
void Cluster::calculateEC(vNode* c) {

	vNode* temp = clusterElements->next;
	int n = 0;
	hNode *t = c->adjNodes;

	while (temp != NULL) {
	//	found = c->neighbours.find(temp->name);
		while (t != NULL) {
			if (t->name == temp->name)
				n++;
			t = t->hNext;
		}
		t = c->adjNodes;
		temp = temp->next;
	}
	noOfEdges += n;
	currentEC = n;
	//return currentEC;
}

double Cluster::densityCalc() {
	double t = abs(noOfNodes) - 1;
	density = static_cast<double>((2 * abs(noOfEdges)) / (abs(noOfNodes)* t));
	return density;
}

double Cluster::calcCP(vNode* c) {
	double cp = static_cast<double>(abs(currentEC) / density * (abs(noOfNodes) - 1));
	return cp;
}

bool Cluster::isAboveThreshold() {
	if (density >= threshDensity && calcCP(currentNode) >= threshCp)
		return true;
	return false;
}

void Cluster::addToCluster(hNode* src) {
	vNode* _new = new vNode();
	_new->name = src->name;
	_new->adjNodes = *src->adjNodes;
	_new->neighbours = *(src->neighbours);
	vNode* temp = NULL;

	if (clusterElements == NULL) {
		clusterElements = _new;
		currentNode = _new;
	}
	else {
		_new->next = clusterElements;
		clusterElements = _new;
		currentNode = _new;
	}
	noOfNodes++;
}

void Cluster::delCurrentNode() {
	vNode* temp2 = clusterElements;
	clusterElements = clusterElements->next;
	currentNode = clusterElements;
	delete temp2;
	noOfNodes--;
	noOfEdges = noOfEdges - currentEC;
	currentEC = 0;
	density = 0;
}


void Cluster::generateNeighbours() {
	hNode* temp = currentNode->adjNodes;
	while (temp != NULL) {
		if (*temp->inNeighbours == false)
			neighbours->push(temp);
		temp = temp->hNext;
	}
	//neighbours->MergeSort(neighbours->head);
	neighbours->sort_list(neighbours->head);
}

void Cluster::cluster(vNode *highest) {


	hNode* second = NULL;

	if (clusterElements == NULL) {
		clusterElements = new vNode();
		clusterElements->name = highest->name;
		clusterElements->neighbours = highest->neighbours;
		clusterElements->adjNodes = highest->adjNodes;
		highest->markCluster(clusterNumber);
		currentNode = clusterElements;
		noOfNodes++;
		generateNeighbours();
	}

	while (neighbours->head != NULL) {
		second = neighbours->head->data;
		neighbours->deqeue();

		if (*second->inCluster == false && *second->clusterNumber == -1) {
			*(second->clusterNumber) = clusterNumber;
			addToCluster(second);
			calculateEC(currentNode);
			densityCalc();
			second->markCluster(clusterNumber);
			if (isAboveThreshold()) {
				//
				//Node now a part of cluster
				//
				this->generateNeighbours();
			}
			else {
				delCurrentNode();
				second->unMark();
			}
		}
	}
}

void Cluster::Print(std::ofstream &out) {
	vNode* c = clusterElements;
	out << clusterNumber << std::endl;
	while (c != NULL)
	{
		out << c->name << std::endl;
		c = c->next;
	}
}