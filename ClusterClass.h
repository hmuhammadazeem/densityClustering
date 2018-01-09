#pragma once
#include <iostream>
#include <fstream>
#include "Stack.h"
#include "NodeClass.h"
#include "HashMap.h"

using namespace std;


class Cluster {
public:
	int clusterNumber = 0;
	double density = 0;

	/*No. of edges within the cluster*/
	int noOfEdges = 0;

	int noOfNodes = 0;

	vNode* clusterElements;
	HashMap *_cElements;

	//Cluster neighbours stack
	myList* neighbours;

	vNode* currentNode;

	//Edge count - number edges of current node with the cluster
	int currentEC = 0;

	//Threshold
	double threshDensity;
	double threshCp;

	Cluster(double d, double cp, int t);
	~Cluster();

	//Member functions
	void calculateEC(vNode* c);
	void densityCalc();
	double calcCP(vNode* c);
	bool isAboveThreshold();
	void addToCluster(hNode* src);
	void delCurrentNode();
	void generateNeighbours();
	void cluster(vNode *highest);
	void Print(ofstream &out);
};

