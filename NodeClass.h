/*
#	This class is the base for the Graphs to be used in this project.
#	Dev        :	 Muhammad Azeem
*/


#pragma once
#include <string>

class hNode {
public:
	std::string name;

	//the edge weight 0 < edge Weight <= 1; given as input
	double edgeWeight;

	//Link to the next node representing the next neighbour
	hNode*  hNext;

	//Pointers to the original node data members in our adjacency list									
	const double *nodeWeight;
	hNode**  adjNodes;
	std::string *neighbours;

	int *degree;
	/*Cluster checks; this attribute is specific to be used during cluster formation*/

	/*Cluster number for identification*/
	int *clusterNumber;

	/*Avoid inclusion in more than one cluster*/
	bool *inCluster;

	/*To avoid repition in neighbours of cluster*/
	bool *inNeighbours;

	/*Marking/Unmarking the cluster number and inCluster attribute*/
	void markCluster(int n);
	void unMark();

	hNode();

};

class vNode {
public:
	std::string name;

	//Sum of all the edge weights
	double nodeWeight;
	

	int degree;

	//Link to the next vertex in the adjacency list
	vNode*  next;

	//Neighbour nodes
	hNode*  adjNodes;

	//String containing names of all the neighbours
	std::string neighbours;

	/*Cluster number for identification*/
	int clusterNumber;

	/*Avoid inclusion in more than one cluster*/
	bool inCluster;

	/*To avoid repition in neighbours of cluster*/
	bool inNeighbours;

	/*Marking/Unmarking the cluster number and inCluster attribute*/
	void markCluster(int n);
	void unMark();

	//Insert new vertex in the adjacency list
	void insertNode(vNode* a, double sweight);

	vNode();
};




