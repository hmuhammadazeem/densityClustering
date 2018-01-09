# densityClustering
Density and cluster property based data clustering program implemented using graph data structure.

<<<<<<< HEAD
The following data structures were used:
# Graph (Undirected)(Adjacency list)
# HashTable
# Stack

# The program uses MergeSort that requires extra stack. So, the following directive should be included to run the program. 
# #pragma comment(linker, "/STACK:2000000")
# You can substitute the sorting algorithm as long as that algorithm doesn't requires discrete data. 
=======
>>>>>>> a709868ed2983fe7dbd08541f41315cd8dd459c8

FILE FORMAT:
[NODE1] [NEIGHBOUR NODE] [EDGE WEIGHT]

Sample Input: 0.5 0.5
Data file:

TFC3	MYO4	0.014
MYO4	SHP1	0.3
GLK1	CLB2	0.015
RVS161	FHL1	0.01

Output clusters:
1
TFC3
SHP1
MYO4
2
CLB2
GLK1
3
FHL1
RVS161

Here is the flow chart that describes the working of this project. More details on working can be found in the /working directory.

![alt text](https://raw.githubusercontent.com/hmuhammadazeem/densityClustering/working/flow.jpg)



