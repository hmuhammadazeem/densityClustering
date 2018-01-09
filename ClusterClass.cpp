#include "ClusterClass.h"


Cluster::Cluster(double d, double cp, int t) {
	clusterNumber = t;
	neighbours = new myList();
	threshCp = cp;
	threshDensity = d;
	_cElements = new HashMap(10);
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
	delete _cElements;
}

//Member functions

void Cluster::calculateEC(vNode* c) {

	hNode* temp = c->adjNodes;
	int n = 0;
	vNode* t;
	while (temp != NULL) {
		if (_cElements->get(HashKey(temp->name), t, temp->name))
			n++;
		temp = temp->hNext;
	}
	noOfEdges += n;
	currentEC = n;
}

void Cluster::densityCalc() {
	double t = (abs(noOfNodes) - 1);
	density = static_cast<double>((2 * abs(noOfEdges)) / (abs(noOfNodes)* t));
}

double Cluster::calcCP(vNode* c) {
	return static_cast<double>(abs(currentEC) / density * (abs(noOfNodes) - 1));
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
	if (_cElements->currentSize >= _cElements->tableSize)
		tableDoubling(_cElements);
	_cElements->put(HashKey(currentNode->name), currentNode);
	noOfNodes++;
}

void Cluster::delCurrentNode() {
	vNode* temp2 = clusterElements;
	clusterElements = clusterElements->next;
	currentNode = clusterElements;
	_cElements->Delete(HashKey(temp2->name), temp2->name);
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
	neighbours->MergeSort(neighbours->head);
}

void Cluster::cluster(vNode *highest) {


	hNode* second = NULL;

	if (clusterElements == NULL) {
		clusterElements = new vNode();
		clusterElements->name = highest->name;
		clusterElements->adjNodes = highest->adjNodes;
		highest->markCluster(clusterNumber);
		currentNode = clusterElements;
		noOfNodes++;
		generateNeighbours();
		_cElements->put(HashKey(currentNode->name), currentNode);
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