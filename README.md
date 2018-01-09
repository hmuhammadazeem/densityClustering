# densityClustering
Density and cluster property based data clustering program implemented using graph data structure.


The following data structures were used: 
Graph (Undirected)(Adjacency list)<br /> 
HashTable<br /> 
Stack<br /> 

The program uses MergeSort that requires extra stack. So, the following directive should be included to run the program. 
pragma comment(linker, "/STACK:2000000")<br /> 
You can substitute the sorting algorithm as long as that algorithm doesn't requires discrete data.<br /> 


FILE FORMAT:<br /> 
[NODE1] [NEIGHBOUR NODE] [EDGE WEIGHT]

Sample Input: 0.5 0.5<br /> 

Data file:<br /> 

TFC3	MYO4	0.014<br /> 
MYO4	SHP1	0.3<br /> 
GLK1	CLB2	0.015<br /> 
RVS161	FHL1	0.01<br /> 

Output clusters:<br /> 
1<br /> 
TFC3<br /> 
SHP1<br /> 
MYO4<br /> 
2<br /> 
CLB2<br /> 
GLK1<br /> 
3<br /> 
FHL1<br /> 
RVS161<br /> 

Here is the flow chart that describes the working of this project. More details on working can be found in the /working directory.<br /> 

![alt text](https://github.com/hmuhammadazeem/densityClustering/blob/master/working/flow.jpg)



